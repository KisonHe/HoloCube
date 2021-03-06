#include "helloworld_app.h"
#include <Arduino.h>
LV_IMG_DECLARE(google);
// lv_obj_t* helloworld_app_logo;

char helloworld_app_name[] = "hello world app";

static app_info_t hello_world_app_info = {
.name = helloworld_app_name,
.logo = google
};

static app_info_t hello_world_app_info_2 = {
.name = "another hello world app",
.logo = google
};
helloworld_app main_helloworld_app(&hello_world_app_info);
helloworld_app main_helloworld_app_2(&hello_world_app_info_2);

helloworld_app::helloworld_app(app_info_t* app_info):app_t(true,nullptr,app_info)
// helloworld_app::helloworld_app(/* args */):app_t(false,nullptr,nullptr)
{
    log_w("hello world constructor of %x, Now app_list is %d long",this,app_list_ptr->size());
    // lv_img_set_src(helloworld_app_logo, &google); how to set the src? cannot call this before lv_init; set another api to be called by menu app
}

helloworld_app::~helloworld_app()
{
    log_w("hello world destructor of %x",this);
}

TickType_t helloworld_app::init(TickType_t tick, intent_t& intent, lv_obj_t* screen){
    app_screen = screen;
    return 1;
}
TickType_t helloworld_app::handle(TickType_t tick){
    return 1;

}
void helloworld_app::deinit(TickType_t tick){
    
}

void helloworld_app::init_app_info(lv_obj_t* img){
    // todo set name according to lang also
    // lv_img_set_src(helloworld_app_logo, &google);
    lv_img_set_src(img, "S:/spiffs/google.bin");
}
