#include "stdio.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
// #include "esp_io_expander_tca9554.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "lvgl_ui.h"
// #include "../components/lvgl_ui/lvgl_ui.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_flash.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "esp_wifi_port.h"
#include "esp_3inch5_lcd_port.h"
#include "esp_psram.h"
#include "esp_private/esp_clk.h"
// #include "esp_sdcard_port.h"

#include "common.h"

const char *TAG = "factory";

i2c_master_bus_handle_t i2c_bus_handle;

esp_lcd_panel_io_handle_t io_handle = NULL;
esp_lcd_panel_handle_t panel_handle = NULL;
// // esp_io_expander_handle_t expander_handle = NULL;
esp_lcd_touch_handle_t touch_handle = NULL;
lv_disp_drv_t disp_drv;

lv_display_t *lvgl_disp = NULL;
lv_indev_t *lvgl_touch_indev = NULL;

bool touch_test_done = false;
// sdmmc_card_t *card = NULL;
int bk_brightness = 30;

#include "driver/temperature_sensor.h"
temperature_sensor_handle_t temp_sensor = NULL;
lv_obj_t *label_brightness;
lv_obj_t *label_flash;
lv_obj_t *label_psram;
lv_obj_t *label_chip_temp;
lv_obj_t *label_chip_freq;
// lv_obj_t *label_sd;


void i2c_bus_init(void);
// void io_expander_init(void);
void lv_port_init(void);

void button_init(void);

void touch_test(void);

static void brightness_slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    int value = lv_slider_get_value(slider);
    bk_brightness = value;
    esp_3inch5_brightness_port_set((uint8_t)value);
    if (label_brightness != NULL) {
        lv_label_set_text_fmt(label_brightness, "%d %%", value);
    }
    printf("Backlight brightness set to %d%%\n", value);
}

static void btn_test_event_handler(lv_event_t *e)
{
    // // lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t *obj = lv_event_get_target(e);
    // if (LV_EVENT_CLICKED != NULL)
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {        
        touch_test_done = false;
        lv_obj_t *lable = NULL;
        if (lvgl_port_lock(0)) {
            lv_obj_clean(lv_scr_act());
            lvgl_port_unlock();
            // then create new objects here
        // }
            vTaskDelay(pdMS_TO_TICKS(100));
            touch_test_done = false;
            touch_test();
        // if (lvgl_port_lock(0))
        // {
            lable = lv_label_create(lv_scr_act());
            lv_label_set_text(lable, "Touch testing mode \nExit with BOOT button");
            lv_obj_center(lable);
            lvgl_port_unlock();
        }
        // vTaskDelay(pdMS_TO_TICKS(100));
        // lv_obj_clean(lv_scr_act());
        // lvgl_port_unlock();
        // lv_port_init();
        // touch_test();
        // lv_obj_del(lable);
        // lvgl_port_unlock();
        printf("Touch test ssstarted.\n");
    }
}


uint32_t flash_size;
uint32_t cpu_freq;
// uint32_t psram_size;

void system_init(void)
{
    esp_flash_get_size(NULL, &flash_size);
    // lv_label_set_text_fmt(label_flash, "%d MB", (int)(flash_size / 1024 / 1024));

    cpu_freq = esp_clk_cpu_freq();
    // lv_label_set_text_fmt(label_chip_freq, "%d MHz", (int)(cpu_freq / 1000 / 1000));

    // psram_size = esp_psram_get_size();
    // lv_label_set_text_fmt(label_psram, "%d MB", (int)(psram_size / 1024 / 1024));

    temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 80);
    temperature_sensor_install(&temp_sensor_config, &temp_sensor);
    temperature_sensor_enable(temp_sensor);
    // temperature_sensor_handle_t tsens = temp_sensor;
}

void tile_init(lv_obj_t *parent)
{
    /*Create a list*/
    lv_obj_t *list = lv_list_create(parent);
    lv_obj_t *lable = lv_label_create(parent);
    // lv_obj_set_style_text_font(lable, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_font(lable, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_label_set_text(lable, "System");
    lv_obj_align(lable, LV_ALIGN_TOP_MID, 0, 3);

    lv_obj_set_size(list, lv_pct(95), lv_pct(80));
    // lv_obj_center(list);
    lv_obj_align(list, LV_ALIGN_TOP_MID, 0, 30);

    lv_obj_t *btn = lv_btn_create(parent);
    lable = lv_label_create(btn);
    lv_label_set_text(lable, "ES8311 Test");
    lv_obj_center(lable);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, -120, -15);
    lv_obj_add_event_cb(btn, btn_test_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t *slider = lv_slider_create(parent);
    lv_slider_set_range(slider, 1, 100);
    lv_slider_set_value(slider, bk_brightness, LV_ANIM_OFF);

    lv_obj_set_size(slider, lv_pct(50), lv_pct(5));
    lv_obj_align(slider, LV_ALIGN_BOTTOM_MID, 75, -18);
    lv_obj_add_event_cb(slider, brightness_slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t *list_item;
    list_item = lv_list_add_btn(list, NULL, "ChipType");
    lv_obj_t *label_chip = lv_label_create(list_item);
    lv_label_set_text(label_chip, "ESP32-S3");
    
    list_item = lv_list_add_btn(list, NULL, "Brightness");
    label_brightness = lv_label_create(list_item);
    lv_label_set_text_fmt(label_brightness, "%d %%", bk_brightness);

    temperature_sensor_handle_t tsens = temp_sensor;
    list_item = lv_list_add_btn(list, NULL, "ChipTemp");
    label_chip_temp = lv_label_create(list_item);
    float temp_value = 0.0f;
    if (tsens != NULL && temperature_sensor_get_celsius(tsens, &temp_value) == ESP_OK) {
        lv_label_set_text_fmt(label_chip_temp, "%.1f Â°C", temp_value);
    } else {
        lv_label_set_text(label_chip_temp, "--- Â°C");
    }

    list_item = lv_list_add_btn(list, NULL, "ChipFreq");
    label_chip_freq = lv_label_create(list_item);
    lv_label_set_text_fmt(label_chip_freq, "%d MHz", (int)(cpu_freq / 1000 / 1000));

    list_item = lv_list_add_btn(list, NULL, "SRAM");
    lv_obj_t *label_ram = lv_label_create(list_item);
    lv_label_set_text(label_ram, "512 KB");

    // list_item = lv_list_add_btn(list, NULL, "PSRAM");
    // label_psram = lv_label_create(list_item);
    // lv_label_set_text_fmt(label_psram, "%d MB", (int)(psram_size / 1024 / 1024));

    // system_init();
    list_item = lv_list_add_btn(list, NULL, "Flash");
    label_flash = lv_label_create(list_item);
    lv_label_set_text_fmt(label_flash, "%d MB", (int)(flash_size / 1024 / 1024));

    // list_item = lv_list_add_btn(list, NULL, "SDCard");
    // label_sd = lv_label_create(list_item);
    // lv_label_set_text(label_sd, "--- MB");
}

#include "../components/ui/ui.h"
// #include "ui.h"

void app_main(void){

    system_init();
    
    ESP_LOGI(TAG, "Initialize backlight");
    gpio_set_direction(EXAMPLE_PIN_NUM_BACKLIGHT, GPIO_MODE_OUTPUT);
    gpio_set_level(EXAMPLE_PIN_NUM_BACKLIGHT, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    i2c_bus_init();
    // io_expander_init();

    esp_3inch5_display_port_init(&io_handle, &panel_handle, LCD_BUFFER_SIZE);    
    // ESP_LOGI(TAG, "panel_handle=%p io_handle=%p", (void *)panel_handle, (void *)io_handle);
    
    esp_3inch5_touch_port_init(&touch_handle, i2c_bus_handle, EXAMPLE_LCD_H_RES, EXAMPLE_LCD_V_RES, EXAMPLE_DISPLAY_ROTATION);
    vTaskDelay(pdMS_TO_TICKS(100));

    // esp_sdcard_port_init();
    esp_wifi_port_init("eero 15", "Znyk97911986Miha!");

    esp_3inch5_brightness_port_init();
    esp_3inch5_brightness_port_set(bk_brightness);
    printf("Backlight brightness set to %d%%\n", (int)bk_brightness);
    lv_port_init();
    
    button_init();
    // touch_test();
    ui_init();

    // tile_init(lv_scr_act());

    lvgl_port_unlock();

    // if (lvgl_port_lock(0))
    // {
    //     // #if LV_USE_DEMO_BENCHMARK
    //     //     lv_demo_benchmark();
    //     // #endif
    //     // #if LV_USE_DEMO_WIDGETS
    //     //     lv_demo_widgets();
    //     // #endif
    //     // if LV_USE_DEMO_MUSIC
    //     //     lv_demo_music();
    //     // #endif
    //     lvgl_ui_init();
    //     lvgl_port_unlock();
    // }
}

void i2c_bus_init(void)
{
    i2c_master_bus_config_t i2c_mst_config = {};
    i2c_mst_config.clk_source = I2C_CLK_SRC_DEFAULT;
    i2c_mst_config.i2c_port = (i2c_port_num_t)I2C_PORT_NUM;
    i2c_mst_config.scl_io_num = EXAMPLE_PIN_I2C_SCL;
    i2c_mst_config.sda_io_num = EXAMPLE_PIN_I2C_SDA;
    i2c_mst_config.glitch_ignore_cnt = 7;
    i2c_mst_config.flags.enable_internal_pullup = 1;

    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &i2c_bus_handle));
}

// void io_expander_init(void)
// {
//     ESP_ERROR_CHECK(esp_io_expander_new_i2c_tca9554(i2c_bus_handle, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000, &expander_handle));
//     ESP_ERROR_CHECK(esp_io_expander_set_dir(expander_handle,  IO_EXPANDER_PIN_NUM_1, IO_EXPANDER_OUTPUT));
//     ESP_ERROR_CHECK(esp_io_expander_set_level(expander_handle, IO_EXPANDER_PIN_NUM_1, 0));
//     vTaskDelay(pdMS_TO_TICKS(100));
//     ESP_ERROR_CHECK(esp_io_expander_set_level(expander_handle, IO_EXPANDER_PIN_NUM_1, 1));
//     vTaskDelay(pdMS_TO_TICKS(100));
// }

void lv_port_init(void)
{
    lvgl_port_cfg_t port_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_port_init(&port_cfg);
    ESP_LOGI(TAG, "Adding LCD screen");
    lvgl_port_display_cfg_t display_cfg = {
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .control_handle = NULL,
        .buffer_size = LCD_BUFFER_SIZE,
        // .double_buffer = false,
        .double_buffer = true,
        .trans_size = 0,
        .hres = EXAMPLE_LCD_H_RES,
        .vres = EXAMPLE_LCD_V_RES,
        .monochrome = false,
        .rotation = {
            .swap_xy = 0,
            .mirror_x = 1,
            .mirror_y = 0,
        },
        .flags = {
            .buff_dma = 0,
            .buff_spiram = 0,
            .sw_rotate = 1,
            .full_refresh = 0,
            .direct_mode = 0,
        },
    };

#if EXAMPLE_DISPLAY_ROTATION == 90
    display_cfg.rotation.swap_xy = 1;
    display_cfg.rotation.mirror_x = 1;
    display_cfg.rotation.mirror_y = 1;
#elif EXAMPLE_DISPLAY_ROTATION == 180
    display_cfg.rotation.swap_xy = 0;
    display_cfg.rotation.mirror_x = 0;
    display_cfg.rotation.mirror_y = 1;

#elif EXAMPLE_DISPLAY_ROTATION == 270
    display_cfg.rotation.swap_xy = 1;
    display_cfg.rotation.mirror_x = 0;
    display_cfg.rotation.mirror_y = 0;
#endif

    // ESP_LOGI(TAG, "Before lvgl_port_add_disp");
    lvgl_disp = lvgl_port_add_disp(&display_cfg);
    // ESP_LOGI(TAG, "After lvgl_port_add_disp: %p", (void *)lvgl_disp);

    if (lvgl_disp == NULL) {
        ESP_LOGE(TAG, "Failed to add LVGL display");
        return;
    }

    // ESP_LOGI(TAG, "Touch init handle before LVGL touch registration: %p", (void *)touch_handle);
    // if (touch_handle == NULL) {
    //     ESP_LOGE(TAG, "Touch handle is NULL; touch controller init failed or was never created");
    //     return;
    // }

    const lvgl_port_touch_cfg_t touch_cfg = {
        .disp = lvgl_disp,
        .handle = touch_handle,
    };
    // ESP_LOGI(TAG, "Before lvgl_port_add_touch: disp=%p handle=%p", (void *)lvgl_disp, (void *)touch_handle);
    lvgl_touch_indev = lvgl_port_add_touch(&touch_cfg);
    // ESP_LOGI(TAG, "After lvgl_port_add_touch: %p", (void *)lvgl_touch_indev);
}

static void button_event_cb(void *arg, void *data)
{
    button_event_t event = iot_button_get_event((button_handle_t)arg);
    ESP_LOGI(TAG, "%s", iot_button_get_event_str(event));
    // touch_test_done = true;
    // Reset flag and enter touch test mode

    // switch (event)
    // {
    // case BUTTON_LONG_PRESS_START:
    //     touch_test_done = false;
    //     if (lvgl_port_lock(0)) {
    //         lv_obj_clean(lv_scr_act());
    //         lvgl_port_unlock();
    //         // then create new objects here
    //     }
    //     vTaskDelay(pdMS_TO_TICKS(100));
    //     touch_test();
    //     printf("Touch test started.\n");
    //     return;
    // case BUTTON_SINGLE_CLICK:
    //     touch_test_done = true;
    //     printf("Touch test completed.\n");
    //     return;
    // // case touch_test_done:
    // //     touch_test_done = true;
    // //     printf("Touch test completed.\n");
    // //     return;
    // default:
    //     break;
    // }
}

void button_init(void)
{
    button_config_t btn_cfg = {};
    button_gpio_config_t btn_gpio_cfg = {};
    btn_gpio_cfg.gpio_num = GPIO_NUM_0;
    btn_gpio_cfg.active_level = 0;
    static button_handle_t btn = NULL;
    ESP_ERROR_CHECK(iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &btn));
    iot_button_register_cb(btn, BUTTON_SINGLE_CLICK, NULL, button_event_cb, NULL);
    iot_button_register_cb(btn, BUTTON_LONG_PRESS_START, NULL, button_event_cb, NULL);
    // iot_button_register_cb(btn, BUTTON_LONG_PRESS_HOLD, NULL, button_event_cb, NULL);
    // iot_button_register_cb(btn, BUTTON_LONG_PRESS_UP, NULL, button_event_cb, NULL);
    // iot_button_register_cb(btn, BUTTON_PRESS_END, NULL, button_event_cb, NULL);
}

// void touch_test(void)
// {
//     uint16_t touchpad_x[1] = {0};
//     uint16_t touchpad_y[1] = {0};
//     uint8_t touchpad_cnt = 0;
//     uint16_t color_arr[16] = {0};
//     lv_obj_t *lable = NULL;

//     for (int i = 0; i < 16; i++)
//     {
//         color_arr[i] = 0xf800;
//     }
//     if (lvgl_port_lock(0))
//     {
//         lable = lv_label_create(lv_scr_act());
//         lv_label_set_text(lable, "Touch testing mode \nExit with BOOT button");
//         lv_obj_center(lable);
//         lvgl_port_unlock();
//     }
//     vTaskDelay(pdMS_TO_TICKS(500));
//     if (lvgl_port_lock(0))
//     {
//         while (!touch_test_done)
//         {
//             /* Read data from touch controller into memory */
//             esp_lcd_touch_read_data(touch_handle);

//             /* Read data from touch controller */
//             esp_lcd_touch_point_data_t point_data[1];
//             uint8_t point_num = 0;
//             esp_lcd_touch_get_data(touch_handle, point_data, &point_num, 1);
            
//             bool touchpad_pressed = (point_num > 0);
//             if (touchpad_pressed && point_num > 0)
//             {
//                 touchpad_x[0] = point_data[0].x;
//                 touchpad_y[0] = point_data[0].y;
//                 touchpad_cnt = point_num;
                
//                 // touchpad_x[0] = EXAMPLE_LCD_H_RES - 1 - touchpad_x[0];

//                 if (touchpad_x[0] < 2)
//                     touchpad_x[0] = 2;
//                 else if (touchpad_x[0] > EXAMPLE_LCD_H_RES - 2 - 1)
//                     touchpad_x[0] = EXAMPLE_LCD_H_RES - 2 - 1;

//                 if (touchpad_y[0] < 2)
//                     touchpad_y[0] = 2;
//                 else if (touchpad_y[0] > EXAMPLE_LCD_V_RES - 2 - 1)
//                     touchpad_y[0] = EXAMPLE_LCD_V_RES - 2 - 1;

//                 esp_lcd_panel_draw_bitmap(panel_handle, touchpad_x[0] - 2, touchpad_y[0] - 2, touchpad_x[0] + 2, touchpad_y[0] + 2, color_arr);
//                 printf("Touch at (%d, %d)\n", touchpad_x[0], touchpad_y[0]);
//             }
//             vTaskDelay(pdMS_TO_TICKS(10));
//         }
//         lv_obj_del(lable);
//         lvgl_port_unlock();
//     }
    
// }
