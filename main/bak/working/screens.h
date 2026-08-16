#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_STRING = 2,
    SCREEN_ID_CONTROL = 3,
    SCREEN_ID_SETTINGS = 4,
    _SCREEN_ID_LAST = 4
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *string;
    lv_obj_t *faults;
    lv_obj_t *control;
    lv_obj_t *settings;
    lv_obj_t *bk_light;
    lv_obj_t *obj0;
    lv_obj_t *can_off;
    lv_obj_t *can_on;
    
    lv_obj_t *header_1;
    lv_obj_t *header_2;
    lv_obj_t *header_3;
    lv_obj_t *header_4;

    lv_obj_t *dropdown_0;
    lv_obj_t *dropdown_1;
    lv_obj_t *dropdown_2;
    lv_obj_t *dropdown_3;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_string();
void tick_screen_string();

void create_screen_control();
void tick_screen_control();

void create_screen_settings();
void tick_screen_settings();

void create_user_widget_header(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_header(int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/