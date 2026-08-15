#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include "wifi_tile.h"

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_main() {
    // lv_obj_t *parent = lv_scr_act();
    // lv_obj_clean(parent);

    lv_obj_t *obj = lv_obj_create(0);
    lv_obj_clean(obj);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 325, 190);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Hello, world!");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button1_btn = obj;
            lv_obj_set_pos(obj, 91, 173);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_button1_pressed, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Button1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Button1");
                }
            }
        }
        {
            // bkLight
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.bk_light = obj;
            lv_obj_set_pos(obj, 28, 45);
            lv_obj_set_size(obj, 425, 34);
            lv_slider_set_value(obj, 25, LV_ANIM_ON);
        }
        {
            // bkl
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.bkl = obj;
            lv_obj_set_pos(obj, 264, 223);
            lv_obj_set_size(obj, 150, 70);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "test");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button2_btn = obj;
            lv_obj_set_pos(obj, 91, 233);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_button2_pressed, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button2 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Button2");
                }
            }
        }
        {
            // header_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 42);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, 6);
            {
                lv_obj_t *parent_obj = obj;
                { 
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.dropdown_0 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
                    lv_dropdown_set_options_static(obj, "Main\nString\nFaults\nControl\nSettings");
                    lv_dropdown_set_selected(obj, 0);
                    lv_obj_add_event_cb(obj, action_main_dropdown_changed, LV_EVENT_VALUE_CHANGED, NULL);
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_scr2() {
    lv_obj_t *obj = lv_obj_create(0);
    lv_obj_clean(obj);
    objects.scr2 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // test
            lv_obj_t *obj = lv_list_create(parent_obj);
            objects.test = obj;
            lv_obj_set_pos(obj, 20, 30);
            lv_obj_set_size(obj, 181, 154);
        }
        {
            lv_obj_t *obj = lv_slider_create(parent_obj);
            lv_obj_set_pos(obj, 36, 237);
            lv_obj_set_size(obj, 407, 22);
            lv_slider_set_value(obj, 25, LV_ANIM_OFF);
        }
        {
            // back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            // objects.back = obj;
            objects.button3_btn = obj;
            lv_obj_set_pos(obj, 330, 82);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_button3_pressed, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button3 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Button3");
                }
            }
        }
        {
            // header_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 42);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, 7);
            {
                lv_obj_t *parent_obj = obj;
                { 
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.dropdown_1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
                    lv_dropdown_set_options_static(obj, "Main\nString\nFaults\nControl\nSettings");
                    lv_dropdown_set_selected(obj, 1);
                    lv_obj_add_event_cb(obj, action_main_dropdown_changed, LV_EVENT_VALUE_CHANGED, NULL);
                }
            }
        }
    }
    
    tick_screen_scr2();
}

void tick_screen_scr2() {
}

void create_screen_lidia_home() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.lidia_home = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button4_btn = obj;
            lv_obj_set_pos(obj, 353, 22);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_button4_pressed, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button4 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Button4");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button6_btn = obj;
            lv_obj_set_pos(obj, 353, 82);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_button6_pressed, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button6 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Button6");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button7_btn = obj;
            lv_obj_set_pos(obj, 353, 146);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_button7_pressed, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button7 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Button7");
                }
            }
        }
        {
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 31, 211);
            lv_obj_set_size(obj, 346, 33);
            lv_slider_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x212529), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xea0b0b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0x938484), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // header_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_3 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 42);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, 8);
            {
                lv_obj_t *parent_obj = obj;
                { 
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.dropdown_2 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
                    lv_dropdown_set_options_static(obj, "Main\nString\nFaults\nControl\nSettings");
                    lv_dropdown_set_selected(obj, 2);
                    lv_obj_add_event_cb(obj, action_main_dropdown_changed, LV_EVENT_VALUE_CHANGED, NULL);
                }
            }
        }
    }
    
    tick_screen_lidia_home();
}

void tick_screen_lidia_home() {
}

void create_screen_ft() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.ft = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // backscr
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.backscr = obj;
            lv_obj_set_pos(obj, 109, 203);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_button5_pressed, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.button5 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Button5");
                }
            }
        }
        {
            // header_4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header_4 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 42);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_header(obj, 9);
            {
                lv_obj_t *parent_obj = obj;
                { 
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.dropdown_3 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
                    lv_dropdown_set_options_static(obj, "Main\nString\nFaults\nControl\nSettings");
                    lv_dropdown_set_selected(obj, 3);
                    lv_obj_add_event_cb(obj, action_main_dropdown_changed, LV_EVENT_VALUE_CHANGED, NULL);
                }
            }
        }
    }
    
    tick_screen_ft();
}

void tick_screen_ft() {
}

void create_user_widget_header(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 313, 14);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_header_menu);
        }
    }
}

void tick_user_widget_header(int startWidgetIndex) {
    (void)startWidgetIndex;
}

// void create_screen_wifi_prov() {
//     lv_obj_t *obj = lv_obj_create(0);
//     objects.wifi_prov = obj;
//     lv_obj_set_pos(obj, 0, 0);
//     lv_obj_set_size(obj, 480, 320);
//     {
//         lv_obj_t *parent_obj = obj;
//         {
//             // Title label
//             lv_obj_t *label = lv_label_create(parent_obj);
//             lv_obj_set_pos(label, 240, 20);
//             lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
//             lv_obj_set_style_text_font(label, &lv_font_montserrat_20, LV_PART_MAIN);
//             lv_label_set_text_static(label, "WiFi Provisioning");
//             lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);
//         }
//         {
//             // SSID label and input
//             lv_obj_t *label = lv_label_create(parent_obj);
//             lv_label_set_text_static(label, "SSID:");
//             lv_obj_set_pos(label, 30, 60);
            
//             lv_obj_t *ssid_ta = lv_textarea_create(parent_obj);
//             lv_obj_set_pos(ssid_ta, 100, 55);
//             lv_obj_set_size(ssid_ta, 350, 30);
//             lv_textarea_set_max_length(ssid_ta, 32);
//             lv_textarea_set_text(ssid_ta, "");
//         }
//         {
//             // Password label and input
//             lv_obj_t *label = lv_label_create(parent_obj);
//             lv_label_set_text_static(label, "Password:");
//             lv_obj_set_pos(label, 30, 110);
            
//             lv_obj_t *pass_ta = lv_textarea_create(parent_obj);
//             lv_obj_set_pos(pass_ta, 100, 105);
//             lv_obj_set_size(pass_ta, 350, 30);
//             lv_textarea_set_max_length(pass_ta, 64);
//             lv_textarea_set_password_mode(pass_ta, true);
//             lv_textarea_set_text(pass_ta, "");
//         }
//         {
//             // Connect button
//             lv_obj_t *btn = lv_btn_create(parent_obj);
//             lv_obj_set_pos(btn, 180, 180);
//             lv_obj_set_size(btn, 120, 50);
//             {
//                 lv_obj_t *label = lv_label_create(btn);
//                 lv_label_set_text_static(label, "Connect");
//                 lv_obj_center(label);
//             }
//         }
//         {
//             // Back button
//             lv_obj_t *btn = lv_btn_create(parent_obj);
//             lv_obj_set_pos(btn, 180, 250);
//             lv_obj_set_size(btn, 120, 50);
//             lv_obj_add_event_cb(btn, action_button3_pressed, LV_EVENT_PRESSED, (void *)0);
//             {
//                 lv_obj_t *label = lv_label_create(btn);
//                 lv_label_set_text_static(label, "Back");
//                 lv_obj_center(label);
//             }
//         }
//     }
    
//     tick_screen_wifi_prov();
// }

// void tick_screen_wifi_prov() {
// }

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_scr2,
    tick_screen_lidia_home,
    tick_screen_ft,
    // tick_screen_wifi_prov,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 4) {
    // if (screen_index >= 0 && screen_index < 5) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "regular_16", &ui_font_regular_16 },
    { "regular_21", &ui_font_regular_21 },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
    create_screen_scr2();
    create_screen_lidia_home();
    create_screen_ft();
    // create_screen_wifi_prov();
}