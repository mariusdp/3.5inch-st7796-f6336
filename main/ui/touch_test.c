
#include "touch_test.h"

#include "esp_lcd_panel_ops.h"

#include "actions.h"
#include "common.h"

static lv_obj_t *touch_test_overlay;

static void touch_test_back_event_cb(lv_event_t *event)
{
    lv_obj_del_async(touch_test_overlay);
    touch_test_overlay = NULL;
    // action_button3_pressed(event);
}

static void touch_test_draw_event_cb(lv_event_t *event)
{
    uint16_t color_arr[16];
    lv_indev_t *indev = lv_indev_get_act();
    lv_point_t touch_point;

    if (indev == NULL)
    {
        return;
    }

    lv_indev_get_point(indev, &touch_point);

    for (int index = 0; index < 16; index++)
    {
        color_arr[index] = 0xf800;
    }

    uint16_t touch_x = touch_point.x;
    uint16_t touch_y = touch_point.y;

    if (touch_x < 2)
        touch_x = 2;
    else if (touch_x > EXAMPLE_LCD_H_RES - 3)
        touch_x = EXAMPLE_LCD_H_RES - 3;

    if (touch_y < 2)
        touch_y = 2;
    else if (touch_y > EXAMPLE_LCD_V_RES - 3)
        touch_y = EXAMPLE_LCD_V_RES - 3;

    esp_lcd_panel_draw_bitmap(panel_handle, touch_x - 2, touch_y - 2, touch_x + 2, touch_y + 2, color_arr);
}

void touch_test_init(lv_obj_t *parent)
{
    if (touch_test_overlay != NULL)
    {
        return;
    }

    touch_test_overlay = lv_obj_create(parent);
    lv_obj_set_size(touch_test_overlay, lv_pct(100), lv_pct(100));
    lv_obj_set_pos(touch_test_overlay, 0, 0);
    lv_obj_add_event_cb(touch_test_overlay, touch_test_draw_event_cb, LV_EVENT_PRESSING, NULL);

    lv_obj_t *back_button = lv_btn_create(touch_test_overlay);
    lv_obj_set_size(back_button, 100, 50);
    lv_obj_align(back_button, LV_ALIGN_TOP_LEFT, 16, 16);
    lv_obj_add_event_cb(back_button, touch_test_back_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label = lv_label_create(back_button);
    lv_label_set_text(label, "Back");
    lv_obj_center(label);
}