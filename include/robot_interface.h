#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>

#include <robot.h>
#include <mapinfo.h>

namespace robot{
    
    using namespace elma;
    using namespace robot;

    class RobotInterface : public Process {
        public:

        RobotInterface(Robot& rs, MapInfo& mp);

        void init(){}
        void start(){}

        void showIntro();
        void showUI();

        //! Update the user interface by (a) reading keyboard input and (b) writing to the screen
        void update();
        void stop() {}

        private:
        Robot& _robot;
        MapInfo& _mapinfo;
    };
}