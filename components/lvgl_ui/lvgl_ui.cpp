#include "lvgl_ui.h"
#include "tileview/image_tile.h"
#include "tileview/wifi_tile.h"

void lvgl_ui_init(void)
{
    lv_obj_t *tileview = lv_tileview_create(lv_scr_act());
    lv_obj_set_style_bg_opa(tileview, LV_OPA_0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tileview, LV_OPA_0, LV_PART_SCROLLBAR | LV_STATE_SCROLLED);

    lv_obj_t *wifi_tile = lv_tileview_add_tile(tileview, 5, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    wifi_tile_init(wifi_tile);
}