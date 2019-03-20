#include <iostream>
#include "gtest/gtest.h"
#include "robot.h"
#include "intruder.h"
#include "mapinfo.h"

namespace {
 
    using namespace elma;
    using namespace robot;

    // More tests go here. You should aim to test every
    // method of every object, either directly or indirectly,
    // although testing user interfaces is notoriously 
    // difficult.
    TEST(Robot, Default){
        Manager m;

        MapInfo mpinfo;
        Intruder intruder(mpinfo);
        Robot robot(&mpinfo);
        RobotInterface ui(robot, mpinfo);

        m.schedule(intruder, 5_s)
        .schedule(robot, 1_s)
        .schedule(ui, 1_s)
        .init()
        .run();
        
        endwin();
    }

    TEST(Robot, JsonFile){
        std::ifstream j_file("test/robot_setting.json");
        json j;
        j_file >> j;
        std::cout << j.dump(4) << std::endl;
        j_file.close();
    }

    TEST(Robot, SettingFromJson) {
        std::ifstream j_file("robot_setting.json");
        json j;
        j_file >> j;
        string robot_name = j["Robot Name"];
        std::cout << robot_name << "\n";
        Setting setting(j);
        j_file.close();
        
        setting.runRobot(); 
        endwin();
    }
}