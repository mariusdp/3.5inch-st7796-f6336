/****************************************************************
**     Pin connections for 3.5" SPI screen ST7796     ***********
**          and I2C touch controller FT6336           ***********
*****************************************************************
**** Screen:   *******************   Touch: *********************
****    MOSI === 11     ***********     SCL === 7     ***********
****    CLK  === 12     ***********     SDA === 8     ***********
****    CS   === 10     ***********                   ***********
****    DC   === 9      ***********                   ***********
****    RST  === 5      ***********                   ***********  
****    BL   === 6      ***********                   ***********
*****************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include "esp_lcd_panel_ops.h"
#include "esp_lcd_touch.h"


#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
// #include "esp_io_expander_tca9554.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_flash.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "esp_wifi_port.h"
#include "esp_3inch5_lcd_port.h"
#include "esp_psram.h"
#include "esp_private/esp_clk.h"
#include "driver/temperature_sensor.h"
// #include "esp_sdcard_port.h"

#include "controls.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG

#define EXAMPLE_PIN_NUM_BACKLIGHT  6
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1

// Touch Pins
#define EXAMPLE_PIN_I2C_SDA GPIO_NUM_8
#define EXAMPLE_PIN_I2C_SCL GPIO_NUM_7

#define EXAMPLE_PIN_BUTTON GPIO_NUM_0

#define EXAMPLE_DISPLAY_ROTATION 270

#if EXAMPLE_DISPLAY_ROTATION == 90 || EXAMPLE_DISPLAY_ROTATION == 270
#define EXAMPLE_LCD_H_RES 480
#define EXAMPLE_LCD_V_RES 320
#else
#define EXAMPLE_LCD_H_RES 320
#define EXAMPLE_LCD_V_RES 480
#endif

#define LCD_BUFFER_SIZE EXAMPLE_LCD_H_RES *EXAMPLE_LCD_V_RES / 8
// #define LCD_BUFFER_SIZE (EXAMPLE_LCD_H_RES * 20)  // or 30, not 320*480/8

#define I2C_PORT_NUM 0

// #define LV_COLOR_16_SWAP 0

// Global variable declarations (definitions are in main.c)
extern const char *TAG;
extern esp_lcd_panel_handle_t panel_handle;
extern esp_lcd_touch_handle_t touch_handle;


#ifdef __cplusplus
}
#endif
#endif

