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

mainmenu_app_t mainmenu_app;
lv_obj_t* mainmenu_app_t::now_app_container = nullptr;
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
        // for (std::vector<app_t*>::iterator it = app_t::app_list.begin(); it != app_t::app_list.end(); it++){
        //     if (*it == this) //skip menu itself
        //         ; //todo change constructor to true to verify this
        //     // 使用Tabview吗？ 
        //     // tabview怎样确保运行中创建/删除的app也会去除对应的tabview？ lv_obj_clean 掉一个tabview,他会自动去掉吗？
        //     // https://forum.lvgl.io/t/how-to-delete-the-tabview-tab/1245/4?u=kisonhe 所以不能用tabview
        //     // 可以切换app的时候，在屏幕外放一个img,动画进来同时另一个动画把现有的img推出去
        // }

        // 直接 show 最开始的app
        index = 0;
        std::vector<app_t*>& vecRef = *app_list_ptr; // vector is not copied here
        app_t* a = vecRef[index];
        log_w("showing app %x with name %s",a,a->get_app_info_ptr()->name);
        a->init_app_info();
        now_app_container = create_app_ctr(app_screen,a->get_app_info_ptr()); // todo how to track app's num, 切换时怎么跟踪下一个是谁
    }

    return 1;
    
}
TickType_t mainmenu_app_t::handle(TickType_t tick){
    // todo 切换动画
    if (index_changed!=0){
        log_w("Noticed change of index");
        index_changed = 0;
        // 清理前一个窗口
        lv_obj_del(now_app_container);
        std::vector<app_t*>& vecRef = *app_list_ptr; // vector is not copied here
        app_t* a = vecRef[index];
        a->init_app_info();
        // 建立新的窗口
        now_app_container = create_app_ctr(app_screen,a->get_app_info_ptr()); // todo how to track app's num, 切换时怎么跟踪下一个是谁
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
lv_obj_t* mainmenu_app_t::create_app_ctr(lv_obj_t * parent, app_info_t* app_info){
    lv_obj_t* ret = lv_obj_create(parent);
    // lv_obj_t* ret = parent;
    lv_obj_set_size(ret,240,240);
    lv_obj_align(ret, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* app_image = lv_img_create(ret);
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
void mainmenu_app_t::init_app_info(){}

/**
 * @brief 
 * 
 * @param dir 0 for mid, 1 for next app and 2 for last app
 */
void mainmenu_app_t::notify_indev(int dir){
    // 如果有左右事件
    // 切换对应app
    if (dir == 0){
        return;//TODO:enter app here
    }
    if (dir == 1){
        index = ((index+1)>=app_list_ptr->size()) ? 0 : index+1;// 下一个app
        index_changed = 1;
    }else if (dir == 2){
        index = (index == 0) ? app_list_ptr->size() -1 : index-1;// 上一个app
        index_changed = -1;
    }
    log_w("now index is %d",index);
}
