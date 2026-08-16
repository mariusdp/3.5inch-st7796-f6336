#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include "stdio.h"
#include "common.h"


extern int lcd_bkl;
extern lv_obj_t *label_lcd_bkl;
extern lv_obj_t *label_lcd_bkl2;
void lcdbkl_event_cb(lv_event_t *e);
void can_event_handler(lv_event_t *e);

#endif