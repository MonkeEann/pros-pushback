#include "main.h"
#include "liblvgl/lvgl.h"

Button::Button(int x, int y, int width, int height, const char* label, pros::Color color)
    : x(x), y(y), width(width), height(height), label(label), color(color) {}
Button::~Button() {}

void Button::draw() {
    if (pressed)
    {
        pros::screen::set_pen(pros::Color::green);
    } else {
        pros::screen::set_pen(color);
    }

    pros::screen::draw_rect(x,y, x + width, y + height);
    pros::screen::set_pen(pros::Color::white);
};

