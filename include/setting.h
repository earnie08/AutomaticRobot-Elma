#ifndef _SETTING_H
#define _SETTING_H

#include "robot.h"
#include "intruder.h"

using namespace elma;
using namespace std;
using namespace robot;

//! \file
namespace robot{
    class Setting{
        public:
        //! Default constructor with json information
        //! \param j jason format setting info
        Setting(json j);

        //! Run the robot
        void runRobot();

        //! Check customize value
        //! \return True: all the setting is reasonable. False: customize value is out of range
        bool checkCustomizeSetting();

        //! Get customize setting information
        //! \return return all customize setting as a string vector
        vector<string> getSetting();

        private:
        int mapsize, amount, rate, detection_area, proximity_area;
        vector<int> station, robot;
        string name;
    };
}
#endif