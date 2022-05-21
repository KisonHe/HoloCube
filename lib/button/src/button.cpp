#include <algorithm>

#include "button.h"
#include "esp32-hal-log.h"
#include "FreeRTOS.h"
#include "freertos/timers.h"
button_setup_t buttonDefaultSetup = {};
button_config_t buttonDefaultConfig = {};
TickSource ButtonTickSource = nullptr;
ButtonHandler ButtonEventHandler = nullptr;
const char* TAG = "button";
bool button::settedUp = false;
std::vector<button*> button::btn_list;

static inline void btn_fire_event(ButtonEventInfo info){
    // ESP_LOGD(TAG,"Got event %d",info.ClickType);
    if (ButtonEventHandler==nullptr)
        ESP_LOGE(TAG,"ButtonEventHandler is null!");
    else
        ButtonEventHandler(info);
}

button::button(gpio_def_t GPIO_def,btn_id_t id,button_config_t btn_config):gpio_def(GPIO_def),id(id),btn_config(btn_config){
    // Check id conflicts
    if(!btn_list.empty()){
        for (std::vector<button*>::iterator it = btn_list.begin(); it != btn_list.end(); it++)
        {
            if ((*it)->id == id){
                ESP_LOGE(TAG,"Duplicate Button ID!"); //Will still continue, Only tell user id is not right.
            }
        }
    }
    btn_list.push_back(this);
    // ESP_LOGD(TAG,"Inited %d btn, now btnlist is %d",this->id,btn_list.size());
}
button::~button(){
    //remove self from btn_list
    //TODO understand this & make sure this is correct
    //https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
    btn_list.erase(std::remove(btn_list.begin(), btn_list.end(), this), btn_list.end()); 
}
/**
 * @brief not safe to call again if false is returned
 * 
 * @param config 
 * @return true 
 * @return false 
 */
bool button::setUp(button_setup_t config){
    if (settedUp){
        ESP_LOGW(TAG,"setUp called more than once");
        return false;
    }
    if (config.selfCall){
        TimerHandle_t btnTimer = xTimerCreate(
                                "ButtonRoutineTimer",
                                pdMS_TO_TICKS(1),
                                pdTRUE,
                                nullptr,
                                [](TimerHandle_t tmr) {Routine(xTaskGetTickCount());}
                                );
        if (btnTimer == nullptr){
            ESP_LOGE(TAG,"Fail to create ButtonRoutineTimer");
            return false;
        }
        // ESP_LOGD(TAG,"Created ButtonRoutineTimer %x",btnTimer);
        if (xTimerStart(btnTimer,pdMS_TO_TICKS(300)) == pdFAIL){
            ESP_LOGE(TAG,"Fail to start ButtonRoutineTimer");
            return false;
        }
    }
    settedUp = true;
    // ESP_LOGD(TAG,"Started ButtonRoutineTimer");
    return true;
}

bool button::IsPressed(){
    return GPIO_ns::Read(gpio_def);
}

TickType_t button::Routine(){
    if (ButtonTickSource == nullptr){
        ESP_LOGE(TAG,"Routine is called without tick source");
        return 0;
    }
    return _Routine(ButtonTickSource());
}

TickType_t button::Routine(TickType_t tick){
    return _Routine(tick);
}

TickType_t button::_Routine(TickType_t tick){
    if (!settedUp){ESP_LOGE(TAG,"button::setUp is not called or have failed");}
    // TickType_t rt = portMAX_DELAY;
    if(!btn_list.empty()){
        for (std::vector<button*>::iterator it = btn_list.begin(); it != btn_list.end(); it++){
            TickType_t tmp = (*it)->_btn_Routine(tick);
            // if (tmp<rt)
            //     rt = tmp;
        }
    }
    // return rt;
    return 1;
}

/**
 * @brief btn handlers called by _Routine. ButtonEventHandler will be called from this function
 * 
 * @param tick int after how many ticks Routine have to be called again
 * @return TickType_t 
 */
TickType_t button::_btn_Routine(TickType_t tick){
    //Pressed, Long, Double, Continuous, Released
    bool nowState;
    nowState = GPIO_ns::Read(gpio_def);
    // if ((tick%1000)==0){
    //     ESP_LOGD(TAG,"Btn%d Routine is called with tick:%d,nowState=%d,state=%d",id,tick,nowState,state);
    //     ESP_LOGD(TAG,"press_start_tick:%d,press_fire_tick=%d,double_debouncing_cnt=%d",press_start_tick,press_fire_tick,double_debouncing_cnt);
    // }
    switch (state)
    {
    case Init: // reset all cnt vars at this stage
        press_start_tick = 0;
        press_fire_tick = 0;
        double_debouncing_cnt = 0;
        state = Inited;
        // ESP_LOGI(TAG,"Btn%d inited",id);
         //Do NOT Break Init because it should go to Inited
    case Inited:
        if (press_start_tick && (nowState != btn_config.PressState)){ //was pressing but not anymore
            // ESP_LOGD(TAG,"Debounced a false press");
            state = Init;
            return 1;
        }
        if (press_start_tick || (nowState == btn_config.PressState)){
            // was pressing or pressing
            if (press_start_tick == 0) press_start_tick = tick;//give value if not set
            
            if ((tick - press_start_tick)>btn_config.DebounceTicks){
                //was pressing and exceed DebounceTicks
                btn_fire_event({id,Pressed});// pressed, fire event
                state = FirstPressed;
                press_fire_tick = tick;
                return 1;
            }
            return 1; //was pressing and not yet exceeded DebounceTicks
        }else{
            //not pressing and wasn't pressing
            press_start_tick = 0;
            return 1;
        }
        break;
    case FirstPressed:
        if (nowState!=btn_config.PressState){
            btn_fire_event({id,Released});// Released, fire event
            press_release_tick = tick;
            state = PressReleased;  //wait for possible double press within double threshold
            return 1;
        }else{
            //still pressing
            if ((tick - press_fire_tick) > btn_config.LongPressThreshold){
                //long should be triggered here
                btn_fire_event({id,Long});// Long, fire event
                state = LongPressed;
                long_press_start_tick = tick;
                return 1;
            }
            //still pressing but tick is not higher and threshold
            return 1;
        }
        break;
    case LongPressed:
        if (nowState!=btn_config.PressState){
            btn_fire_event({id,Released});// Released, fire event
            state = Init;  //long will not get another double
            return 1;
        }else{
            //still pressing
            if ((tick - long_press_start_tick) > btn_config.ContinuousPressInitialDuration){
                //long should be triggered here
                btn_fire_event({id,Continuous});// Long, fire event
                state = ContinuousPressing;
                long_press_start_tick = tick;
                return 1;
            }
            //still pressing but tick is not higher and threshold
            return 1;
        }
        break;
    case ContinuousPressing:
        if (nowState!=btn_config.PressState){
            btn_fire_event({id,Released});// Released, fire event
            state = Init;  //continue will not get another double
            return 1;
        }else{
            //still pressing
            if ((tick - long_press_start_tick) > btn_config.ContinuousPressInterval){
                //long should be triggered here
                btn_fire_event({id,Continuous});// Long, fire event
                state = ContinuousPressing;
                long_press_start_tick = tick;
                return 1;
            }
            //still pressing but tick is not higher and threshold
            return 1;
        }
        break;
    case PressReleased:
        if (nowState==btn_config.PressState){
            // a double press
            state = DoubleDebouncing;  //Pressing again! Do a Debouncing
            return 1;
        }else{
            //not pressing
            if ((tick - press_release_tick) > btn_config.DoubleClickThreshold){
                // not pressing for too long, no longer any double
                // release fired last release
                // ESP_LOGD(TAG,"Double Fail at tick %d with press_release_tick %d",tick,press_release_tick);
                state = Init;
                return 1;
            }
            //still not pressing but tick is not higher than double threshold
            return 1;
        }
        break;
    case DoubleDebouncing:
        // slightly different here, if not pressing anymore will not clear to init until threshold is reached
        if (nowState!=btn_config.PressState){
            double_debouncing_cnt = 0; // clear cnt
            //not pressing, we can tolerate until threshold is reached
            if ((tick - press_fire_tick) > btn_config.DoubleClickThreshold){
                //too long since last press, not a double!
                state = Init;
                //no need to fire release here
                return 1;
            }
            return 1;
        }else{
            //pressing
            double_debouncing_cnt++;
            if (double_debouncing_cnt > btn_config.DebounceTicks){
                // double confirmed.
                btn_fire_event({id,Double});
                state = DoubleWaitRelease;
                return 1;
            }
            //still pressing but tick is not higher than debounce threshold
            return 1;
        }
        break;
    case DoubleWaitRelease:
        if (nowState!=btn_config.PressState){
            //Finally the button is released
            btn_fire_event({id,Released});
            state = Init;
            return 1;
        }
        return 1; // Still pressing
        break;
        
    default:
        ESP_LOGE(TAG,"Unexpected State at btn%d. Resetting to Init",id);
        state = Init;
        return 1;
    }
    ESP_LOGE(TAG,"Control flow should not get here");

}

