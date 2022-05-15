#include "mainTabView.h"
#include <lvgl.h>
#include "fonts.h"

// static void scroll_begin_event(lv_event_t * e)
// {
//     /*Disable the scroll animations. Triggered when a tab button is clicked */
//     if(lv_event_get_code(e) == LV_EVENT_SCROLL_BEGIN) {
//         lv_anim_t * a = (lv_anim_t *)lv_event_get_param(e);
//         if(a)  a->time = 0;
//     }
// }

void lv_main_tabview_init(void)
{
    /*Create a Tab view object*/
    // lv_obj_t * tabview;
    // tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 50);
    // lv_obj_add_event_cb(lv_tabview_get_content(tabview), scroll_begin_event, LV_EVENT_SCROLL_BEGIN, NULL);

    // lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    // lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    // lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    // lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);
    // lv_obj_set_style_text_font(tab_btns,p_custom_font,0);


    // /*Add 4 tabs (the tabs are page (lv_page) and can be scrolled*/
    // lv_obj_t * motorTab = lv_tabview_add_tab(tabview, "电机");
    // lv_obj_t * controlTab = lv_tabview_add_tab(tabview, "控制");
    // lv_obj_t * sensorTab = lv_tabview_add_tab(tabview, "传感器");
    // lv_obj_t * networkTab = lv_tabview_add_tab(tabview, "网络");
    // lv_motor_tab_init(motorTab);
    // lv_control_tab_init(controlTab);
    // lv_sensor_tab_init(sensorTab);
    // lv_network_tab_init(networkTab);

    // lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);
}
