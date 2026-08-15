#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// extern void action_rtn_main(lv_event_t * e);
extern void action_button1_pressed(lv_event_t * e);
extern void action_button2_pressed(lv_event_t * e);
extern void action_button3_pressed(lv_event_t * e);
extern void action_button4_pressed(lv_event_t * e);
extern void action_button5_pressed(lv_event_t * e);
extern void action_button6_pressed(lv_event_t * e);
extern void action_button7_pressed(lv_event_t * e);
extern void action_main_dropdown_changed(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/