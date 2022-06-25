/**
 * @file mainmenu_app.cpp
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "mainmenu_app.h"
#include "esp32-hal-log.h"
#include "../stringtable.h"
#include "../style/style.h"
#include "maganer.h"
mainmenu_app_t mainmenu_app;
lv_obj_t* mainmenu_app_t::now_app_container = nullptr;
lv_obj_t* mainmenu_app_t::next_app_container = nullptr;
mainmenu_app_t* mainmenu_app_t::mainmenu_app_ptr = nullptr;
mainmenu_app_t::mainmenu_app_t(/* args */):app_t(false,nullptr,nullptr){  
    if (mainmenu_app_ptr!=nullptr){
        log_e("FATAL: Multi instance of mainmenu_app");
        abort();
    }
    mainmenu_app_ptr = this;
}

mainmenu_app_t::~mainmenu_app_t(){
    mainmenu_app_ptr = nullptr;
}

mainmenu_app_t* mainmenu_app_t::get_mainmenu_app_ptr(){
    return mainmenu_app_ptr;
}

TickType_t mainmenu_app_t::init(TickType_t tick, intent_t& intent, lv_obj_t* screen){
    ESP_LOGD(TAG,"app_list %x is %d long",app_list_ptr,app_list_ptr->size());
    app_screen = screen;
    lv_obj_add_style(app_screen,&default_style,LV_STATE_DEFAULT);

    if (app_t::app_list_ptr->size() < 1){
        //no apps
        show_no_app();
    }else{
        // 直接 show 最开始的app
        index = 0;
        std::vector<app_t*>& vecRef = *app_list_ptr; // vector is not copied here
        app_t* a = vecRef[index];
        log_d("showing app %x with name %s",a,a->get_app_info_ptr()->name);
        now_app_container = create_app_ctr(app_screen,a->get_app_info_ptr(),a); 
        // log_v("Pos x is %d, y %d",lv_obj_get_x(now_app_container),lv_obj_get_y(now_app_container));
    }

    return 1;
    
}
TickType_t mainmenu_app_t::handle(TickType_t tick){
    if (enterApp){
        enterApp = false;
        lv_obj_del(now_app_container);
        std::vector<app_t*>& vecRef = *app_list_ptr; // vector is not copied here
        app_t* a = vecRef[index];
        app_manager::app_pass_intent({
            this,
            a,
            nullptr  //Arduino json?
            //data,last_app,current_app etc. last_app在manager那里检查一下,确保是正确的
        });
    }
    if ((!busy)&&(index_changed!=0)){
        log_d("Noticed change of index %d type %d",index,index_changed);
        int16_t now_start_x;
        int16_t now_end_x;
        int16_t old_start_x;
        int16_t old_end_x;
        int16_t unit = 300;
        if (index_changed>0){
            now_start_x = -184;
            now_end_x = 0;
            old_start_x = 0;
            old_end_x = 184;
        }else{
            now_start_x = 184;
            now_end_x = 0;
            old_start_x = 0;
            old_end_x = -184;
        }
        index_changed = 0;

        // lv_anim_path_linear lv_anim_path_bounce
        // lv_anim_path_overshoot lv_anim_path_ease_out
        // lv_anim_path_step
        if (app_t::app_list_ptr->size() >1){
            std::vector<app_t*>& vecRef = *app_list_ptr; // vector is not copied here
            app_t* a = vecRef[index];
            // 建立新的窗口
            next_app_container = create_app_ctr(app_screen,a->get_app_info_ptr(),a);

            lv_anim_t now_app;
            lv_anim_init(&now_app);
            now_app.path_cb=lv_anim_path_ease_out;
            lv_anim_set_exec_cb(&now_app, (lv_anim_exec_xcb_t)lv_obj_set_x);
            lv_anim_set_var(&now_app, next_app_container);
            lv_anim_set_values(&now_app, now_start_x, now_end_x);
            uint32_t duration = lv_anim_speed_to_time(unit, now_start_x, now_end_x); // 计算时间
            lv_anim_set_time(&now_app, duration);

            lv_anim_t pre_app;
            lv_anim_init(&pre_app);
            pre_app.path_cb=lv_anim_path_ease_out;
            lv_anim_set_exec_cb(&pre_app, (lv_anim_exec_xcb_t)lv_obj_set_x);
            lv_anim_set_var(&pre_app, now_app_container);
            lv_anim_set_values(&pre_app, old_start_x, old_end_x);
            duration = lv_anim_speed_to_time(unit, old_start_x, old_end_x); // 计算时间
            lv_anim_set_time(&pre_app, duration);

            lv_anim_start(&now_app);
            lv_anim_start(&pre_app);

            busy = true;
            return 1;
        }
        if (busy){
            if (!lv_anim_count_running()) {
                busy=false;
                lv_obj_del(now_app_container);
                now_app_container = next_app_container;
            }
        }
    }else{
        // Only one app. Maybe add some anime
    }
    return 1;
}
void mainmenu_app_t::deinit(TickType_t tick){
    // 所有app的deinit都不需要清理建在app_screen里面的东西，manager会清理的
}
LV_IMG_DECLARE(warn_logo);
void mainmenu_app_t::show_no_app(){
    // log_d("mainmenu_app_t::init with tick%d,screen%x",tick,screen);
    //-------------
    lv_obj_t* ret = lv_obj_create(app_screen);
    // lv_obj_t* ret = app_screen;
    //make ret max size with no margins, like a container in lvgl 7, 

    lv_obj_t* app_image = lv_img_create(ret);
    lv_img_set_src(app_image, &warn_logo);
    lv_obj_align(app_image, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t* app_name = lv_label_create(ret);
    lv_obj_add_style(ret, &default_style, 0); // todo selector
    lv_label_set_text(app_name, "No apps installed"); // todo set font also,maybe need to change the struct
    lv_obj_align_to(app_name, app_image, LV_ALIGN_OUT_BOTTOM_MID,0,0);
}
/**
 * @brief 记得clean掉原来的，不会主动clean
 * 
 * @param parent 
 * @param app_info 
 * @return lv_obj_t* 
 */
lv_obj_t* mainmenu_app_t::create_app_ctr(lv_obj_t * parent, app_info_t* app_info, app_t* the_app){
    lv_obj_t* ret = lv_obj_create(parent);
    // lv_obj_t* ret = parent;
    lv_obj_set_size(ret,180,200);
    lv_obj_align(ret, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* app_image = lv_img_create(ret);
    the_app->init_app_info(app_image);
    
    lv_img_set_src(app_image, &app_info->logo);
    lv_obj_align(app_image, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t* app_name = lv_label_create(ret);
    assert(app_name!=nullptr);
    lv_obj_add_style(ret, &default_style, 0); // todo selector
    lv_label_set_text(app_name, app_info->name); // todo set font also,maybe need to change the struct
    lv_obj_align_to(app_name, app_image, LV_ALIGN_OUT_BOTTOM_MID,0,0);
    return ret;
}
/**
 * @brief 用不到
 * 
 */
void mainmenu_app_t::init_app_info(lv_obj_t* img){}

/**
 * @brief 
 * 
 * @param dir 0 for mid, 1 for next app and 2 for last app
 */
void mainmenu_app_t::notify_indev(int dir){
    if (app_manager::get_now_running_app()!=this){
        return;
    }
    // 如果有左右事件
    // 切换对应app
    log_d("notify_indev got dir %d",dir);
    if (dir == 0 && (!busy)){
        enterApp = true;
        return;//TODO:enter app here
    }
    if (dir == 1){
        index = ((index+1)>=app_list_ptr->size()) ? 0 : index+1;// 下一个app
        index_changed = 1;
    }else if (dir == 2){
        index = (index == 0) ? app_list_ptr->size() -1 : index-1;// 上一个app
        index_changed = -1;
    }
    log_d("now index is %d",index);
}
