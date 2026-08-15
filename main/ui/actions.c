#include "actions.h"
#include "screens.h"
#include "ui.h"
#include "wifi_tile.h"
#include "touch_test.h"

void action_button1_pressed(lv_event_t * e) {loadScreen(SCREEN_ID_STRING);} // Navigate to screen scr2
void action_button2_pressed(lv_event_t * e) {loadScreen(SCREEN_ID_CONTROL);} // Navigate to screen lidia_home
void action_button3_pressed(lv_event_t * e) {loadScreenBack(SCREEN_ID_MAIN);} // Navigate to main screen
void action_button4_pressed(lv_event_t * e) {loadScreenBack(SCREEN_ID_MAIN);} // Navigate to main screen
void action_button5_pressed(lv_event_t * e) {button5_init(lv_scr_act());} // Navigate to wifi tile
void action_button6_pressed(lv_event_t * e) {loadScreen(SCREEN_ID_SETTINGS);} // Navigate to screen ft
void action_button7_pressed(lv_event_t * e) {touch_test_init(lv_scr_act());} // Navigate to touch test
/*
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_STRING = 2,
    SCREEN_ID_CONTROL = 3,
    SCREEN_ID_SETTINGS = 4,
    _SCREEN_ID_LAST = 4
    */
// void action_main_dropdown_changed(lv_event_t * e)
// {
//     lv_obj_t *dropdown = lv_event_get_target(e);

//     switch (lv_dropdown_get_selected(dropdown))
//     {
//     case 0:
//         loadScreen(SCREEN_ID_MAIN);
//         lv_dropdown_set_selected(objects.dropdown_0, 0);
//         break;
//     case 1:
//         loadScreen(SCREEN_ID_SCR2);
//         lv_dropdown_set_selected(objects.dropdown_1, 1);
//         break;
//     case 2:
//         loadScreen(SCREEN_ID_LIDIA_HOME);
//         lv_dropdown_set_selected(objects.dropdown_2, 2);
//         break;
//     case 3:
//         loadScreen(SCREEN_ID_FT);
//         lv_dropdown_set_selected(objects.dropdown_3, 3);
//         break;
//     default:
//         break;
//     }
// }