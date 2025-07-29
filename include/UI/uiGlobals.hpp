#ifndef UI_GLOBALS_HPP
#define UI_GLOBALS_HPP

#include "main.h"
#include "liblvgl/lvgl.h"

extern pros::Task* lvglTask;
extern pros::Task* printPIDTask;


enum screenType {
    HOME_SCREEN,
    ODOM_SCREEN,
    PID_SCREEN,
    TERMINAL_SCREEN
    // Add more screens as needed
};

LV_FONT_DECLARE(modak_40);
LV_FONT_DECLARE(modak_20);
LV_FONT_DECLARE(modak_24);

extern lv_obj_t* home_screen;

extern lv_obj_t* odom_screen;

extern lv_obj_t* pid_screen;

extern lv_obj_t* terminal_screen;
extern lv_obj_t* terminalTextArea;

extern lv_obj_t* medic_screen;

void lvgl_task_fn(void*);

void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p);

void initializeGUI();

void containerStyle(lv_obj_t* parent);
void buttonSetup(lv_obj_t* parent);
void screenSetup(lv_obj_t* parent);
void buildFooter(lv_obj_t* parent);
void exitButtonCb(lv_event_t * e);

#endif //UI_GLOBALS_HPP