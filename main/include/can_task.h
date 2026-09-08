#ifndef __CAN_TASK_H__
#define __CAN_TASK_H__

#include "stdio.h"
#include "common.h"

#define CAN_TX 4
#define CAN_RX 5
#define PERIOD_100MS   100     
#define PERIOD_500MS   500    
#define PERIOD_1000MS  1000  
#define CAN_TIMEOUT_MS 5000
#define DEBUG_CAN
extern uint8_t heartbeat_counter;
extern uint32_t heartbeat_uptime;
extern volatile bool can_alive;
extern volatile uint64_t last_batlimits_rx_us;

void can_init(void);
void can_receive_task(void *pvParameters);
void can_tx_task(void *pvParameters);
extern volatile float pwm_current;
extern volatile uint32_t pwm_duty;
extern volatile float max_charge_current;
#define PWM_MAX_DUTY       ((1 << 11) - 1)    // 10 > 1023 | 11 > 2047 | 12 > 4095 | 13 > 8191 | 14 > 16383 | 15 > 32767 | 16 > 65535


#endif