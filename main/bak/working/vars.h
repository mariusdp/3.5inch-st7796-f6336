#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_SELECTED_USER = 0,
    FLOW_GLOBAL_VARIABLE_TOGGLE_BUTTON_STATE = 1
};

// Native global variables

extern int32_t get_var_selected_user();
extern void set_var_selected_user(int32_t value);
extern int32_t get_var_toggle_button_state();
extern void set_var_toggle_button_state(int32_t value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/