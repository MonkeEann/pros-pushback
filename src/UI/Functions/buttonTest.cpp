#include "main.h"
#include "liblvgl/lvgl.h"

void buttonTest() {
    lv_tick_set_cb(pros::millis);
    lv_display_t * display = lv_display_create(480,240);

    static uint8_t buf1[480 * 240 / 8 * 2];
    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
}
