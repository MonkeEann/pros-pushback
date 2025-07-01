#ifndef TOGGLE_BUTTON_HPP
#define TOGGLE_BUTTON_HPP

#include "button.hpp"

class toggleButton : public Button {
public:
    std::vector<std::string> states;
    std::vector<const uint8_t*> imageBuffers;
    std::vector<int> imageSizes;

    int currentState = 0;
    bool wasPressedLastFrame = false;
    bool colorSwitch;

    toggleButton(int x, int y, int width, int height, const char* label, pros::Color color, std::vector<std::string> stateList, std::vector<const uint8_t*> imageList, std::vector<int> sizeList, bool colorSwitch);

    void draw() override;
    void drawCustom();
    void update();
    std::string getCurrentState();
    int getStateIndex();
};

#endif