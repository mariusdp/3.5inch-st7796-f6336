#include "controls.h"
#include "screens.h"

int lcd_bkl = 30;
lv_obj_t *label_lcd_bkl = NULL;
lv_obj_t *label_lcd_bkl2 = NULL;

int value = 30; 

// can_off toggles its own CHECKED state via LV_OBJ_FLAG_CHECKABLE; react to it here
void can_event_handler(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);

    if (lv_obj_has_state(target, LV_STATE_CHECKED)) {
        printf("CAN on %p\n", target);
        value = 10;
        // lcd_bkl = 10;
        esp_3inch5_brightness_port_set((uint8_t)value);
        // esp_3inch5_brightness_port_set((uint8_t)lcd_bkl);
    } else {
        printf("CAN off %p\n", target);
        value = 90;
        esp_3inch5_brightness_port_set((uint8_t)value);
        // lcd_bkl = 90;
        // esp_3inch5_brightness_port_set((uint8_t)lcd_bkl);
    }
}
// static void lcdbkl_event_cb(lv_event_t *e)
void lcdbkl_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    int value = lv_slider_get_value(slider);
    lcd_bkl = value;
    esp_3inch5_brightness_port_set((uint8_t)value);
    if (label_lcd_bkl != NULL) {
        lv_label_set_text_fmt(label_lcd_bkl, "%d %%", value);
        // lv_slider_set_value(label_lcd_bkl, value32, LV_ANIM_OFF);
    }
    if (label_lcd_bkl2 != NULL) {
        lv_label_set_text_fmt(label_lcd_bkl2, "%d %%", value);
        // lv_slider_set_value(label_lcd_bkl2, value32, LV_ANIM_OFF);
    }
    #ifdef DEBUG
    printf("Backlight brightness set to %d%%\n", value);
    #endif
} 
