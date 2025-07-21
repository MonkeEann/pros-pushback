#ifndef UTIL_GLOBALS
#define UTIL_GLOBALS

extern pros::Task* printBattery;

void deleteLines(int startLine, int endLine);
void printToTerminal(int lineIndex, const char* message);

void getBattery();

void batteryTaskFn(void* param);
void debugTaskFn(void* param);

#endif //UTIL_GLOBALS