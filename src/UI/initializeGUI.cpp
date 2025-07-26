#include "main.h"
#include "liblvgl/lvgl.h"
#include "uiGlobals.hpp"

void lvgl_task_fn(void*) {
    while (true) {
        lv_timer_handler();
        //pros::Task::delay_until(pros::millis() + 5); // Adjust the delay as needed
        pros::delay(5);
    }
}

void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p){
    for (int y = area->y1; y <= area->y2; y++){
        for (int x = area ->x1; x <= area->x2; x++){
            
            int width = area->x2 - area->x1 + 1;
            int index = (y - area->y1) * width + (x - area->x1);

            uint16_t color = ((uint16_t *)color_p)[index];

            // Write the pixel to your display
            pros::screen::set_pen(pros::Color(color));
            pros::screen::draw_pixel(x, y);
        }
    }

    lv_display_flush_ready(disp);
}

void initializeGUI() {
    // Initialize and give time source to start LVGL
    lv_init();
    lv_tick_set_cb(pros::millis);

    // Create Display
    lv_display_t * display = lv_display_create(480,240);

    static uint8_t buf1[480 * 240 / 10 * 2];
    
    //Create Buffer and set buffer mode as well as flush callback (cb)
    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_display_set_flush_cb(display, my_flush_cb);

    lv_theme_t * theme = lv_theme_default_init(
        display, 
        lv_palette_darken(LV_PALETTE_BLUE_GREY, 3), 
        lv_palette_darken(LV_PALETTE_BLUE, 4), 
        true,
        &lv_font_montserrat_20);

    lv_display_set_theme(display, theme);
    
    //Create All the Screens
    home_screen = lv_obj_create(NULL);
    odom_screen = lv_obj_create(NULL);
    pid_screen = lv_obj_create(NULL);
    terminal_screen = lv_obj_create(NULL);
    medic_screen = lv_obj_create(NULL);

    // BUILD UI
    terminalScreen();
    homeScreen();
    odomScreen();
    pidScreen();
    medicScreen();
    
    //Start GUI Task
    lvglTask = new pros::Task(lvgl_task_fn, nullptr, "GUI");

    // Start on Home Screen
    lv_screen_load(home_screen);
    
    bool isScreensInit = 
    (home_screen != nullptr) &&
    (terminal_screen != nullptr) &&
    (pid_screen != nullptr) &&
    (odom_screen != nullptr) &&
    (medic_screen != nullptr);
    // Check GUI Status
    if (isScreensInit){
        printToTerminal(8, "GUI STATUS: ACTIVE");
    }
}

 