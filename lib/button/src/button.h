/**
 * @file button.h
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief No blocking functions, enjoy!
 * @version 0.1
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BUTTON_H
#define BUTTON_H
#include <vector>
#include "gpio.h"

typedef uint32_t TickType_t;
typedef uint8_t btn_id_t;

typedef struct {
    bool selfCall = true; // will use a freertos timer to call Routine
} button_setup_t;

extern button_setup_t buttonDefaultSetup;

typedef struct {
    uint8_t PressState = 0;                             // HIGH or LOW, state when pressed
    TickType_t DebounceTicks = 5;                       // How long it has to stay pressed for Debounce in ticks. 0 will disable Debounce
    TickType_t LongPressThreshold = 500;                // How long it has to stay pressed AFTER Press event fire, to trigger long press. In ticks. 
    TickType_t DoubleClickThreshold = 500;               // Max ticks between clicks to trigger double press. In ticks. 
    TickType_t ContinuousPressInitialDuration = 500;    // How long AFTER LongPressThreshold will fire first ContinuousPress event. 
    TickType_t ContinuousPressInterval = 20;            // How long AFTER ContinuousPressInitialDuration will fire another ContinuousPress event. 
} button_config_t;

extern button_config_t buttonDefaultConfig;

// https://docs.lvgl.io/8.2/overview/event.html#handle-multiple-events
// https://docs.lvgl.io/8.2/overview/event.html#input-device-events 
enum ClickType_t{
    Pressed,
    Long,
    Double, 
    Continuous, 
    Released
};
struct ButtonEventInfo {
    btn_id_t ButtonId;
    ClickType_t ClickType;
};
typedef void (*ButtonHandler)(ButtonEventInfo info);
/**
 * @brief the ButtonEventHandler will be called when event happens.
 * the function is called from Routine(), better NOT BLOCK this function
 * 
 */
extern ButtonHandler ButtonEventHandler;

typedef TickType_t (*TickSource)(void);
/**
 * @brief The function providing tick source, can set to nullptr 
 * but have to call Routine with ticks
 * 
 * 
 */
extern TickSource ButtonTickSource;

class button
{
private:
    /* data */
    TickType_t press_start_tick = 0;         //used for debounce
    TickType_t press_fire_tick = 0;  // when is last press triggered. used to calculate possible long and double click
    TickType_t long_press_start_tick = 0; // when is last long triggered,used to calculate possible 
    TickType_t double_debouncing_cnt = 0;
    TickType_t press_release_tick = 0;
    static std::vector<button*> btn_list; //for Routine to run
    static TickType_t _Routine(TickType_t tick);
    TickType_t _btn_Routine(TickType_t tick);
    static TickType_t wake_time;
    static bool settedUp;
    gpio_def_t gpio_def;
    enum State_t{
        Init,
        Inited,
        InitPressdebouncing,
        FirstPressed,
        PressReleased,
        DoubleDebouncing,
        DoubleWaitRelease,
        LongPressed,
        ContinuousPressing
    };
    State_t state = Init;
    btn_id_t id;
    button_config_t btn_config; 

public:
    static bool setUp(button_setup_t config);

    /**
     * @brief return direct gpio read value. No debounce. You can call it without calling setUp
     * @return true direct gpio read value
     * @return false direct gpio read value
     */
    bool IsPressed();

    /**
     * @brief call this periodically, if call this version 
     * TickSource ButtonTickSource must be set first
     * @return int after how many ticks Routine have to be called again(not implemented, should call at 1khz for now)
     * if something is not right will return 0
     */
    static TickType_t Routine();

    /**
     * @brief call this periodically
     * 
     * @param tick now tick
     * @return int after how many ticks Routine have to be called again(not implemented, should call at 1khz for now)
     */
    static TickType_t Routine(uint32_t tick);

    button(gpio_def_t GPIO_def,btn_id_t id,button_config_t btn_config);   //constructor, add self to btn_list and check id conflict, set gpio, button_config_t etc
    button() = delete;
    ~button();
};



#endif //BUTTON_H
