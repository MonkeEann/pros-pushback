#ifndef BUILDHOMESCREEN_HPP
#define BUILDHOMESCREEN_HPP

void buildHomeScreen();
void buildMainButtons();
void buildToggles();

extern const char* mainLabels[4];

extern lv_obj_t* toggleable[3];
extern lv_obj_t* toggle_labels[3];
extern const char* toggleOff[3];
extern const char* toggleOn[3];

void toggleCB(lv_event_t* e);

#endif // BUILDHOMESCREEN_HPP