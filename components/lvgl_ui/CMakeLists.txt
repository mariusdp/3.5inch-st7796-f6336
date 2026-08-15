file(GLOB_RECURSE SRC_FILES "*.cpp")


idf_component_register(SRCS ${SRC_FILES}
                    INCLUDE_DIRS "."
                    REQUIRES "lvgl" 
                            "freertos" 
                            "spi_flash" 
                            "esp_psram" 
                            "driver" 
                            "esp_hw_support" 
                            "espressif__esp_lvgl_port" 
                            "esp_port")
                    