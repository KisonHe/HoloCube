/**
 * @file maganer.h
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "app.h"

namespace app_manager{
    void manager_init();
    void manager_handle();
    esp_err_t app_pass_intent(intent_t intent);
    esp_err_t app_exit();
}