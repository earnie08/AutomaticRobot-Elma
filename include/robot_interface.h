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

        //! Constructor with Rpbpt class and MapInfo class and customize setting info
        //! \param rs Robot Class
        //! \param mp MapInfo Class
        //! \param customizeSetting Default is empty
        RobotInterface(Robot& rs, MapInfo& mp, vector<string> customizeSetting = vector<string>());

        void init(){}
        void start(){}

        //! Show information about the robot
        void showIntro();

        //! Show robot status
        void showUI();

        //! Update the user interface by (a) reading keyboard input and (b) writing to the screen
        void update();
        void stop() {}

        private:
        Robot& _robot;
        MapInfo& _mapinfo;
        vector<string> _customize;
    };
}