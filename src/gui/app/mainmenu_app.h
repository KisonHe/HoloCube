/**
 * @file mainmenu_app.h
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "app.h"

// Menu app should be Singleton
// https://stackoverflow.com/questions/27338175/how-to-create-class-with-only-one-instance-in-c
class mainmenu_app_t : public app_t
{
private:
    mainmenu_app_t(/* args */);
public:
    // uint8_t createMainMenuApp
    static mainmenu_app_t * const mainmenu_app_ptr;
    ~mainmenu_app_t();
};