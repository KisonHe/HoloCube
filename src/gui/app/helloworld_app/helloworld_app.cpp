#include "helloworld_app.h"

LV_IMG_DECLARE(google);
lv_obj_t* helloworld_app_logo;

char helloworld_app_name[] = "hello world app";

// app_info_t hello_world_app_info;// = {
// .name = helloworld_app_name,
// .logo = helloworld_app_logo
// };

// helloworld_app::helloworld_app(/* args */):app_t(false,nullptr,&hello_world_app_info)

helloworld_app::helloworld_app(/* args */):app_t(false,nullptr,nullptr)
{
    lv_img_set_src(helloworld_app_logo, &google);
}

helloworld_app::~helloworld_app()
{
}
