#ifndef BUILD_PID_SCREEN
#define BUILD_PID_SCREEN
#include "liblvgl/lvgl.h"

extern lv_obj_t* PIDbuttons[6];
extern lv_obj_t* PIDlabels[6];

extern lv_obj_t* modeToggleBtn;
extern bool isAdditionMode;

extern lv_obj_t* incrementButtons[3];
extern int selectedIncrementIndex;

extern const char* pidLabels[2][3];
extern double prevValues[6];
extern double currentIncrement;

void initPrevValues();
void PIDScreenInit();

struct PIDEditContext;
void adjustPIDCallback(lv_event_t* e);

void containerStyle(lv_obj_t* parent);
void buildPIDScreen();
void buildIncrementContainer(lv_obj_t* parent);
void increment_btn_cb(lv_event_t* e);
void printPIDScreenTaskFn(lv_timer_t* timer);
void toggle_mode_cb(lv_event_t* e);

#endif  //BUILD_PID_SCREEN