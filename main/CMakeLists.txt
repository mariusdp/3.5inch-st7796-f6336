# file(GLOB_RECURSE srcs "main.c" "src/*.c" "src/*.cpp" "ui/*.c" "ui/images/*.c" )
file(GLOB_RECURSE srcs "main.c" "src/*.c" "src/*.cpp" "ui/*.c" "ui/*.cpp" "ui/images/*.c" )
list(APPEND srcs "src/controls.c" "src/can_task.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "." "./include" "./ui"
                    REQUIRES "lvgl" 
                            "freertos" 
                            "spi_flash" 
                            "esp_psram" 
                            "driver" 
                            "esp_hw_support" 
                            "fatfs"
                            "nvs_flash"
                            "esp_wifi"
                            "espressif__esp_lvgl_port" 
                            "esp_lcd"
                            "espressif__esp_lcd_touch"
                            )


