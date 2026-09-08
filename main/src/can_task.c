
#include "can_task.h"

uint8_t heartbeat_counter = 0;
uint32_t heartbeat_uptime = 0;
// static uint8_t heartbeat_counter = 0;
// static uint32_t heartbeat_uptime = 0;
volatile bool can_alive = false;
volatile uint64_t last_batlimits_rx_us = 0;

volatile float pwm_current = 0.0f;
volatile uint32_t pwm_duty = 0;
volatile float max_charge_current = 0.0f;

int can_currentv = 0;

typedef enum{
    HEARTBEAT_OK    = 0x55,
    HEARTBEAT_FAULT = 0xAA,
} heartbeat_status_t;
static heartbeat_status_t heartbeat_status = HEARTBEAT_OK;

typedef enum {
    CAN_ID_BatLimits        = 0x358,
    CAN_ID_InvMeas          = 0x360,
    CAN_ID_InvFeedback      = 0x3E0,
    CAN_ID_InvInit          = 0x560,
    /**/
    CAN_ID_ReceivedLimits   = 0x450,
    CAN_ID_Sorenson         = 0x451,
    /**/
    CAN_ID_Heartbeat        = 0x7E0,
} can_id_t;

typedef struct {
    float max_charge_voltage;
    float max_discharge_voltage;
    float max_discharge_current;
    float max_charge_current;
} bat_limits_t;
static bat_limits_t bat_limits;

// Initialize the CAN interface
void can_init(void)
{
    twai_general_config_t g_config =
        TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX, CAN_RX, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config =
        TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config =
        TWAI_FILTER_CONFIG_ACCEPT_ALL();
    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
    ESP_ERROR_CHECK(twai_start());
}

// Helper function to send a CAN message
static esp_err_t can_send_message(uint32_t id, const uint8_t data[8])
{
    twai_message_t msg = {
        .identifier = id,
        .data_length_code = 8,
        .flags = TWAI_MSG_FLAG_NONE,
    };
    memcpy(msg.data, data, 8);
    return twai_transmit(&msg, 0);
}

// Helper function to pack four float values into a byte array (10x4 format)
static void pack_float10x4(uint8_t data[8], float v1, float v2, float v3, float v4)
{
    uint16_t value[4];
    value[0] = (uint16_t)(v1 * 10.0f);
    value[1] = (uint16_t)(v2 * 10.0f);
    value[2] = (uint16_t)(v3 * 10.0f);
    value[3] = (uint16_t)(v4 * 10.0f);
    for (int i = 0; i < 4; i++) {
        data[i * 2]     = (uint8_t)(value[i] >> 8);
        data[i * 2 + 1] = (uint8_t)(value[i] & 0xFF);
    }
}

// Task to send CAN messages every 500ms
void can_send_500ms(void){
    uint8_t data[8];
    /*--------------------------------------
     * CAN ID 0x450 - Battery Limits
     *--------------------------------------*/
    pack_float10x4(
        data,
        bat_limits.max_charge_voltage,
        bat_limits.max_discharge_voltage,
        bat_limits.max_discharge_current,
        bat_limits.max_charge_current);
    esp_err_t err450 = can_send_message(CAN_ID_ReceivedLimits, data);

    if (err450 != ESP_OK) {
        printf("ID 0x450 failed: %s\n", esp_err_to_name(err450));
    }
    /*--------------------------------------
     * CAN ID 0x451 - PWM / Charger Status
     *--------------------------------------*/
    pack_float10x4(
        data,
        pwm_current,                        // Actual PWM current
        // voltage * 10.0f,                    // PWM output voltage
        (3.3f * pwm_duty) / PWM_MAX_DUTY,   // PWM output voltage
        (100.0f * pwm_duty) / PWM_MAX_DUTY, // PWM %
        bat_limits.max_charge_current       // Requested current
    );
    esp_err_t err451 = can_send_message(CAN_ID_Sorenson, data);

    if (err451 != ESP_OK) {
        printf("ID 0x451 failed: %s\n", esp_err_to_name(err451));
    }
}

void can_send_heartbeat(void)
{
    uint8_t data[8] = {0};
    heartbeat_counter++;
    heartbeat_uptime++;
    data[0] = heartbeat_counter;
    data[1] = heartbeat_status;
    // data[2] = can_alive;
    data[2] = can_alive ? 1 : 0;
    // uptime in seconds
    data[3] = (heartbeat_uptime >> 24) & 0xFF;
    data[4] = (heartbeat_uptime >> 16) & 0xFF;
    data[5] = (heartbeat_uptime >> 8) & 0xFF;
    data[6] = heartbeat_uptime & 0xFF;
    // reserved
    data[7] = 0;
    #ifndef DEBUG_CAN
    if (can_send_message(CAN_ID_Heartbeat, data) == ESP_OK)
    {
        printf("Heartbeat %u sent\n", heartbeat_counter);
    }
    #else
    esp_err_t err = can_send_message(CAN_ID_Heartbeat, data);

    if (err != ESP_OK) {
        printf("ID 0x701 failed: %s\n", esp_err_to_name(err));
    }
    #endif
        vTaskDelay(pdMS_TO_TICKS(10));
    // if (bat_limits.max_charge_voltage <= 0.0f)
    // {
    //     heartbeat_status = HEARTBEAT_FAULT;
    // }
    // else
    // {
    //     heartbeat_status = HEARTBEAT_OK;
    // }
}


// // Check if the CAN messages are being received within the timeout period
// void can_watchdog_check(void)
// {
//     uint64_t now = esp_timer_get_time();
//     if ((now - last_batlimits_rx_us) > (CAN_TIMEOUT_MS * 6000ULL))
//     {
//         can_alive = false;
//         heartbeat_status = HEARTBEAT_FAULT;
//         // Safe state
//         // pwm_set_current(0.0f);
//     }
//     // else if (bat_limits.max_charge_voltage <= 10.0f){
//     //     // can_alive = true;
//     //     heartbeat_status = HEARTBEAT_FAULT;
//     //     // Safe state
//     //     // pwm_set_current(0.0f);
//     // }
//     else
//     {
//         heartbeat_status = HEARTBEAT_OK;
//     }
// }

// Task to send CAN messages periodically
void can_tx_task(void *arg)
{
    TickType_t last100ms = xTaskGetTickCount();
    TickType_t last500ms = xTaskGetTickCount();
    TickType_t last1000ms = xTaskGetTickCount();
    while (1)
    {
        TickType_t now = xTaskGetTickCount();
        // if ((now - last100ms) >= pdMS_TO_TICKS(PERIOD_100MS))
        // {
        //     last100ms = now;
        //     can_send_100ms();
        //     taskYIELD();
        // }
        if ((now - last500ms) >= pdMS_TO_TICKS(PERIOD_500MS))
        {
            last500ms = now;
            can_send_500ms();
            taskYIELD();
        }
        if ((now - last1000ms) >= pdMS_TO_TICKS(PERIOD_1000MS))
        {
            last1000ms = now;
            // Send heartbeat message every 1 second
            // can_watchdog_check();
            can_send_heartbeat();
            taskYIELD();
        }
    }
}

// Task to receive CAN messages
void can_receive_task(void *arg)
{
    twai_message_t message;
    while (1) {
        if (twai_receive(&message, pdMS_TO_TICKS(1000)) == ESP_OK) {
            // Ignore extended frames
            if (message.flags & TWAI_MSG_FLAG_EXTD) {
                continue;
            }

            
            if((can_id_t)message.identifier != NULL){
                can_alive = true;
                printf("message pointer is valid\n");
            }
            else{
                can_alive = false;
                printf("Error: unexpected CAN message ID\n");
                // vTaskDelete(NULL);
            }


            switch ((can_id_t)message.identifier) {
                case CAN_ID_BatLimits: {
                    if (message.data_length_code == 8) {
                        last_batlimits_rx_us = esp_timer_get_time();
                        // can_alive = true;
                        float values[4];
                        // uint16_t values[4];
                        for (int i = 0; i < 4; i++) {
                            uint16_t raw = ((uint16_t)message.data[i * 2] << 8) |
                                        message.data[i * 2 + 1];
                            // values[i] = (((uint16_t)message.data[i * 2] << 8) |
                            //             message.data[i * 2 + 1]) / 10f;
                            /**/
                            values[i] = raw / 10.0f;
                        }
                        #ifndef DEBUG_CAN
                        printf("CAN-ID: 0x%03lx DLC:%d Data:",
                            message.identifier,
                            message.data_length_code);
                        for (int i = 0; i < message.data_length_code; i++) {
                            printf(" %02X", message.data[i]);
                        }
                        printf("\n");
                        #endif
                        bat_limits.max_charge_voltage = values[0];
                        bat_limits.max_discharge_voltage = values[1];
                        bat_limits.max_discharge_current = values[2];
                        bat_limits.max_charge_current = values[3];
                        max_charge_current = bat_limits.max_charge_current;
                        #ifdef DEBUG_CAN
                        printf("MaxCharge:%.1f V  MaxDischarge:%.1f V  MaxDischargeCurrent:%.1f A  MaxChargeCurrent:%.1f A  Act. current: %.1f A\n",
                            bat_limits.max_charge_voltage,
                            bat_limits.max_discharge_voltage,
                            bat_limits.max_discharge_current,
                            bat_limits.max_charge_current,
                            pwm_current);
                            /**/
                            // chg_cur = values[3];
                            #endif
                    }
                    break;
                }
                case CAN_ID_InvMeas: {
                    if (message.data_length_code == 8) {
                        float values[4];
                        // uint16_t values[4];
                        for (int i = 0; i < 4; i++) {
                            uint16_t raw = ((uint16_t)message.data[i * 2] << 8) |
                                        message.data[i * 2 + 1];
                            // values[i] = (((uint16_t)message.data[i * 2] << 8) |
                            //             message.data[i * 2 + 1]) / 10f;
                            values[i] = raw / 10.0f;
                        }
                        #ifndef DEBUG_CAN
                        printf("CAN-ID: 0x%03lx DLC:%d Data:",
                            message.identifier,
                            message.data_length_code);
                        for (int i = 0; i < message.data_length_code; i++) {
                            printf(" %02X", message.data[i]);
                        }
                        printf("\n");
                        #endif
                    }
                    break;
                }
                case CAN_ID_InvFeedback: {
                    if (message.data_length_code == 8) {
                        float values[4];
                        // uint16_t values[4];
                        for (int i = 0; i < 4; i++) {
                            uint16_t raw = ((uint16_t)message.data[i * 2] << 8) |
                                        message.data[i * 2 + 1];
                            // values[i] = (((uint16_t)message.data[i * 2] << 8) |
                            //             message.data[i * 2 + 1]) / 10f;
                            /**/
                            values[i] = raw / 10.0f;
                        }
                    }
                    break;
                }
                default:
                    // Unknown CAN ID
                    printf("Error: unexpected CAN message ID: 0x%03lx\n", message.identifier);
                    break;
            }
        }
        // vTaskDelay(pdMS_TO_TICKS(10));
    }
}