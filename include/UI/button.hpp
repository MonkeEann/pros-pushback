#ifndef BUTTON_HPP
#define BUTTON_HPP

class Button {
    public:
    int x, y, width, height;
    const char* label;
    pros::Color color;
    bool pressed;

    Button(int x, int y, int width, int height, const char* label, pros::Color color);

    virtual ~Button();
    
    virtual void draw();
    void drawCustom(const uint8_t* buttonImage, int startX, int startY, int imageSize);
    bool ispressing();
    void updatePressed();
    bool isPressed();
};

#endif