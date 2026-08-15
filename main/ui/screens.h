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
    SCREEN_ID_SCR2 = 2,
    SCREEN_ID_LIDIA_HOME = 3,
    SCREEN_ID_FT = 4,
    _SCREEN_ID_LAST = 4
    // SCREEN_ID_WIFI_PROV = 5,
    // _SCREEN_ID_LAST = 5
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *scr2;
    lv_obj_t *lidia_home;
    lv_obj_t *ft;
    // lv_obj_t *wifi_prov;
    lv_obj_t *bk_light;
    lv_obj_t *bkl;
    lv_obj_t *test;
    lv_obj_t *back;
    lv_obj_t *obj0;
    lv_obj_t *backscr;


    lv_obj_t *button1_btn;
    lv_obj_t *button1;
    lv_obj_t *button2_btn;
    lv_obj_t *button2;
    lv_obj_t *button3_btn;
    lv_obj_t *button3;
    lv_obj_t *button4_btn;
    lv_obj_t *button4;
    lv_obj_t *button5;
    lv_obj_t *button6_btn;
    lv_obj_t *button6;
    lv_obj_t *button7_btn;
    lv_obj_t *button7;

    lv_obj_t *dropdown_0;
    lv_obj_t *dropdown_1;
    lv_obj_t *dropdown_2;
    lv_obj_t *dropdown_3;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_scr2();
void tick_screen_scr2();

void create_screen_lidia_home();
void tick_screen_lidia_home();

void create_screen_ft();
void tick_screen_ft();

// void create_screen_wifi_prov();
// void tick_screen_wifi_prov();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/