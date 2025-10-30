#ifndef BUILDHOMESCREEN_HPP
#define BUILDHOMESCREEN_HPP

#include "liblvgl/misc/lv_types.h"

void buildHomeScreen();
void buildMainButtons();
void buildToggles();

extern const char* mainLabels[4];

extern lv_obj_t* toggleable[2];
extern lv_obj_t* toggle_labels[2];

extern lv_obj_t* autonSwitcher;
extern lv_obj_t* autonSwitcherLabel;

extern const char* toggleOff[2];
extern const char* toggleOn[2];
/*
 * Callback functions for the main buttons
 */
void toggleCB(lv_event_t* e);
void autonCB(lv_event_t* e);
void odomCb(lv_event_t& e);
void pidCb(lv_event_t& e);
void terminalCb(lv_event_t& e);
void medicCb(lv_event_t& e);


#endif // BUILDHOMESCREEN_HPP