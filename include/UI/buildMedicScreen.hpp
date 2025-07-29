#ifndef BUILD_MEDIC_SCREEN
#define BUILD_MEDIC_SCREEN
#include "liblvgl/lvgl.h"
#include <iostream>
#include <vector>
#include "roboConfig.hpp"

extern lv_obj_t* motorInfoContainers[10];
extern lv_obj_t* motorTA[10];
extern const char* motorLabels[10];
extern double temperatures[10];
extern int32_t voltage[10];
extern int32_t current[10];

void reload_btn_cb(lv_event_t* e);
void buildMedicScreen();
void drawLabels();
void updateMotorData();

#endif //BUILD_MEDIC_SCREEN