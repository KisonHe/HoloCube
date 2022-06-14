#include "tomato_timer.h"
#include <Arduino.h>
char tomato_app_name[] = "Tomato Timer";
LV_IMG_DECLARE(tomato);
static app_info_t tomato_app_info = {
.name = tomato_app_name,
.logo = tomato
};

tomato_timer::tomato_timer(/* args */):app_t(true,nullptr,&tomato_app_info)
{
}

tomato_timer::~tomato_timer()
{
}

TickType_t tomato_timer::init(TickType_t tick, intent_t& intent, lv_obj_t* screen){
    app_screen = screen;
    log_w("init of tomato app!");
    lv_obj_t* text_lable = lv_label_create(app_screen);
    assert(text_lable!=nullptr);
    // lv_obj_add_style(ret, &default_style, 0); // todo selector
    lv_label_set_text(text_lable, "Welcome to tomato timer"); // todo set font also,maybe need to change the struct
    lv_obj_align(text_lable, LV_ALIGN_CENTER, 0, 0);
    return 1;
}
TickType_t tomato_timer::handle(TickType_t tick){
    return 1;

}
void tomato_timer::deinit(TickType_t tick){
    
}

void tomato_timer::init_app_info(lv_obj_t* img){
    // todo set name according to lang also
    // lv_img_set_src(helloworld_app_logo, &google);
    // lv_img_set_src(img, "S:/spiffs/google.bin");
}

// tomato
tomato_timer main_tomato_timer;