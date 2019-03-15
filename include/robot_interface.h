#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>

#include "robot_core.h"

namespace robot{
    using namespace elma;
    using namespace robot;

    class RobotInterface : public Process {
        RobotInterface(Robot_Core& rc);

        void init(){}
        void start(){}

        void show_layout(){}

        //! Update the user interface by (a) reading keyboard input and (b) writing to the screen
        void update();
        void stop() {}

    };
}