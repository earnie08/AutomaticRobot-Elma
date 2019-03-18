#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>

#include "robot.h"
#include "intruder.h"


using namespace std::chrono;
using namespace elma;
using namespace robot;

int main() {
    Manager m;

    MapInfo mpinfo;
    Intruder intruder(mpinfo);
    Robot states(&mpinfo);
    RobotInterface ui(states, mpinfo);

    m.schedule(intruder, 5_s)
     .schedule(states, 1_s)
     .schedule(ui, 1_s)
     .init()
     .run();
     
    endwin();
}  
