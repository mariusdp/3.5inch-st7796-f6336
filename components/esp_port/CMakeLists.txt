file(GLOB_RECURSE SRC_FILES "*.cpp")

idf_component_register(SRCS ${SRC_FILES}
                    INCLUDE_DIRS "."
                    REQUIRES "freertos" 
                            "driver" 
                            "fatfs" 
                            "nvs_flash" 
                            "lwip" 
                            "esp_wifi" 
                            "esp_lcd_st7796" 
                            "esp_lcd_touch_ft6336")
