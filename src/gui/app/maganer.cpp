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
namespace app_manager{

static app_t* now_app = nullptr;
static bool inited = false;
// static app* default_app = 
/**
 * @brief should be called first
 * 
 */
void manager_init(){
    if (inited)
        return;
    if (mainmenu_app_t::mainmenu_app_ptr!=nullptr)
        mainmenu_app_t::mainmenu_app_ptr = new mainmenu_app_t();
    // now_app = mainmenuapp's address
}

void manager_handle(){
    
}

}