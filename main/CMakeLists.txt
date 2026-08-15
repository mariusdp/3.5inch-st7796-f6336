file(GLOB_RECURSE srcs "main.c" "src/*.c" "src/*.cpp" "ui/*.c" )

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "." "./include" "./ui"
                    REQUIRES "lvgl" 
                            # "lvgl_ui"
                            "freertos" 
                            "spi_flash" 
                            "esp_psram" 
                            "driver" 
                            "esp_hw_support" 
                            "fatfs"
                            "nvs_flash"
                            "esp_wifi"
                            "espressif__esp_lvgl_port" 
                            # "esp_port"
                            "esp_lcd"
                            "espressif__esp_lcd_touch"
                            )


