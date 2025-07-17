#ifndef UI_GLOBALS_HPP
#define UI_GLOBALS_HPP

#include "main.h"
#include "liblvgl/lvgl.h"


enum screenType {
    HOME_SCREEN,
    ODOM_SCREEN,
    PID_SCREEN,
    TERMINAL_SCREEN
    // Add more screens as needed
};

extern lv_obj_t* home_screen;
extern lv_obj_t* odom_screen;
extern lv_obj_t* pid_screen;
extern lv_obj_t* terminal_screen;

void lvgl_task_fn(void*);

void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p);

void initializeGUI();

#endif //UI_GLOBALS_HPP