#include "stdio.h"
#include "common.h"
#include "ui.h"

const char *TAG = "factory";

i2c_master_bus_handle_t i2c_bus_handle;

// // esp_io_expander_handle_t expander_handle = NULL;
esp_lcd_panel_io_handle_t io_handle = NULL;
esp_lcd_panel_handle_t panel_handle = NULL;
esp_lcd_touch_handle_t touch_handle = NULL;
lv_disp_drv_t disp_drv;

lv_display_t *lvgl_disp = NULL;
lv_indev_t *lvgl_touch_indev = NULL;

bool touch_test_done = false;
// sdmmc_card_t *card = NULL;
int bk_brightness = 30;

// int can_currentv = 0;

temperature_sensor_handle_t temp_sensor = NULL;
lv_obj_t *label_brightness;
lv_obj_t *label_flash;
lv_obj_t *label_psram;
lv_obj_t *label_chip_temp;
lv_obj_t *label_chip_freq;
// lv_obj_t *label_sd;
// lv_obj_t *label_can_current;

uint32_t flash_size;
uint32_t cpu_freq;
// uint32_t psram_size;

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

void app_main(void){
    can_init();
    xTaskCreatePinnedToCore(can_receive_task, "can_rx", 4096, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(can_tx_task, "can_tx", 4096, NULL, 4, NULL, 1);
    // xTaskCreate(can_receive_task, "can_rx", 4096, NULL, 5, NULL);
    // xTaskCreate(can_tx_task, "can_tx", 4096, NULL, 4, NULL);
    
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
    esp_3inch5_brightness_port_set(lcd_bkl);
    // printf("Backlight brightness set to %d%%\n", (int)lcd_bkl);
    // esp_3inch5_brightness_port_set(bk_brightness);
    // printf("Backlight brightness set to %d%%\n", (int)bk_brightness);
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

    switch (event)
    {
    case BUTTON_LONG_PRESS_START:
        // touch_test_done = false;
        // if (lvgl_port_lock(0)) {
        //     lv_obj_clean(lv_scr_act());
        //     lvgl_port_unlock();
        //     // then create new objects here
        // }
        // vTaskDelay(pdMS_TO_TICKS(100));
        // touch_test();
        // printf("Touch test started.\n");
        esp_restart();
        return;
    case BUTTON_SINGLE_CLICK:
        // touch_test_done = true;
        printf("Long press to reset.\n");
        return;
    // case touch_test_done:
    //     touch_test_done = true;
    //     printf("Touch test completed.\n");
    //     return;
    default:
        break;
    }
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
