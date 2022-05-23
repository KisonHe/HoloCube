/**
 * @file maganer.cpp
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "maganer.h"
#include "app.h"
#include "mainmenu_app.h"
#include "lvgl.h"
#include "FreeRTOS.h"
#include "esp32-hal-log.h"

static const char* TAG = "manager";
namespace app_manager{

enum State_t{
    Init,
    Running,
    Quit
};

struct now_app_config_t
{
    mainmenu_app_t* now_app = nullptr;
    // logo shown to user, should be no more than 128x128
    State_t state = Init;
    lv_obj_t* screen = nullptr;
};

static now_app_config_t now_app_config;
static bool inited = false;
// static app* default_app = 
/**
 * @brief should be called first
 * 
 */
void manager_init(){
    if (inited)
        return;
    if (now_app_config.now_app != nullptr){
        ESP_LOGE(TAG,"When initing, now_app is not nullptr! Will not run now_app's deinit");
    }
    now_app_config.now_app = mainmenu_app_t::get_mainmenu_app_ptr();
    if (now_app_config.screen != nullptr){
        ESP_LOGE(TAG,"When initing, screen is not nullptr! Will not clean screen");
    }else{
        now_app_config.screen = lv_obj_create(nullptr);
        if (now_app_config.screen == nullptr){
            ESP_LOGE(TAG,"Fail to create screen");
        }
    }
    lv_scr_load(now_app_config.screen);
    ESP_LOGD(TAG,"Loaded screen");
    intent_t init_intent = {nullptr,now_app_config.now_app,nullptr};
    now_app_config.now_app->init(xTaskGetTickCount(),init_intent,now_app_config.screen);
    inited = true;
}

void manager_handle(){
    if (now_app_config.now_app == nullptr){
        ESP_LOGE(TAG,"Running manager_handle but now_app is nullptr");
        now_app_config.now_app = mainmenu_app_t::get_mainmenu_app_ptr();
    }
    now_app_config.now_app->handle(xTaskGetTickCount());
}

/**
 * @brief The api an app calls for switching app.
 * 
 * @param intent 
 * @return esp_err_t 
 */
esp_err_t app_pass_intent(intent_t intent){
    //TODO
    return ESP_OK;

}

/**
 * @brief The api an app calls if it want to quit TO Menu
 * Just a wrapper of app_pass_intent
 * 
 * @return esp_err_t 
 */
esp_err_t app_exit(){

}

}
