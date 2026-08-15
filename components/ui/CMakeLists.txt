idf_component_register(SRCS "ui.c" "screens.c" "images.c" "styles.c" "actions.c" "wifi_tile.c" "touch_test.c"
                    REQUIRES "lvgl" 
                            "esp_port" 
                            "esp_lcd" 
                            "driver" 
                            "espressif__esp_lcd_touch" 
                            "espressif__esp_lvgl_port"
                            )

