#ifndef UTIL_GLOBALS
#define UTIL_GLOBALS


void deleteLines(int startLine, int endLine);
void printToTerminal(int lineIndex, const char* message);

void getBattery();

void batteryTaskFn(void* param);
void debugTaskFn(void* param);
void controllerTaskFn(void* param);


void initRobot();
#endif //UTIL_GLOBALS