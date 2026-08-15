
idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES "lvgl" 
                            "lvgl_ui"
                            "freertos" 
                            "spi_flash" 
                            "esp_psram" 
                            "driver" 
                            "esp_hw_support" 
                            "espressif__esp_lvgl_port" 
                            "esp_port"
                            "esp_lcd"
                            "espressif__esp_lcd_touch"
                            "ui"
                            )


