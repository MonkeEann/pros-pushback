#ifndef AUTO_GLOBALS_HPP
#define AUTO_GLOBALS_HPP
#include "string"
#include "vector"
#include <string>

class auton {
    private:
        std::string name;
        void (*routine)();
    public:
        auton(std::string Name, void (*routineFunc)());
        std::string getName() const;
        void run();
        
};
class autonManager {
    private:
        std::vector<auton> autons;
        int selectedAutonIndex = -1;

    public:
    void selectAuton(std::string name);
    void selectAuton(int index);
    void runSelectedAuton();
    void addAuton(std::string name, void (*routineFunc)());
    void listAutons();
    int getAutonNum() const;
    std::string getSelectedAutonName() const;
    std::string getAutonName(int index) const;
    
};

void configureAutons();
void leftAutonWP();
void rightAutonWP();
void taxiAuton();
void longOnlyLeftAuton();
void longOnlyRightAuton();
#endif // AUTO_GLOBALS_HPP