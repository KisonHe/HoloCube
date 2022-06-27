#include "settings_app.h"
#include <Arduino.h>
LV_IMG_DECLARE(placeholder_img);
// lv_obj_t* settings_app_logo;

char settings_app_name[] = "Settings";

static app_info_t settings_app_info = {
.name = settings_app_name,
.logo = placeholder_img
};

settings_app main_settings_app(&settings_app_info);
// settings_app main_settings_app_2(&hello_world_app_info_2);

settings_app::settings_app(app_info_t* app_info):app_t(true,nullptr,app_info)
// settings_app::settings_app(/* args */):app_t(false,nullptr,nullptr)
{
    // log_v("hello world constructor of %x, Now app_list is %d long",this,app_list_ptr->size());
    // lv_img_set_src(settings_app_logo, &google); how to set the src? cannot call this before lv_init; set another api to be called by menu app
}

settings_app::~settings_app()
{
    // log_v("hello world destructor of %x",this);
}

TickType_t settings_app::init(TickType_t tick, intent_t& intent, lv_obj_t* screen){
    app_screen = screen;
    // log_d("init of helloworld app!");
    text_lable = lv_label_create(app_screen);
    assert(text_lable!=nullptr);
    // lv_obj_add_style(ret, &default_style, 0); // todo selector
    lv_label_set_text(text_lable, "Hello World!"); // todo set font also,maybe need to change the struct
    lv_obj_align(text_lable, LV_ALIGN_CENTER, 0, 0);
    return 1;
}
TickType_t settings_app::handle(TickType_t tick){
    cnt++;
    if (cnt>1000){
        lv_label_set_text(text_lable, "Hello World!");
        cnt=0;
    }else if(cnt>500){
        lv_label_set_text(text_lable, "Hello World!~");
    }
    return 1;

}
void settings_app::deinit(TickType_t tick){
    
}

void settings_app::init_app_info(lv_obj_t* img){
    // todo set name according to lang also
    // lv_img_set_src(settings_app_logo, &google);
    // lv_color_t color  = lv_color_white();
    // lv_img_set_src(img, LV_SYMBOL_SETTINGS);
    // lv_obj_set_style_img_recolor(img, color, 0);
    log_e("settings init_app_info");
    lv_img_set_src(img, "S:/spiffs/settings_icon.bin");
}
