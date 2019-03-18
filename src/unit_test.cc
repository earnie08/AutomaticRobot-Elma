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
        Robot states(&mpinfo);
        RobotInterface ui(states, mpinfo);

        m.schedule(intruder, 5_s)
        .schedule(states, 1_s)
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

    // TEST(Robot, SettingFromJson) {
    //     std::ifstream j_file("test/robot_setting.json");
    //     json j;
    //     j_file >> j;


    //     for (json::iterator it = j.begin(); it != j.end(); ++it) {
    //         std::cout << it.key() << " : " << it.value() << "\n";
    //     }

    //     string robot_name = j["Robot Name"];
    //     std::cout << robot_name <<"\n";
        
    //     string mode = j["Mode"];
    //     std::cout << mode <<"\n";
        
    //     int map_size = j["MapSize"];
    //     std::cout << map_size << "\n";
        
    //     int battery_size = j["BatterySize"];
    //     int battery_consume_rate = j["BatteryConsumeRate"];
    //     vector<int> charge_station = j["ChargeStation"];
    //     vector<int> robot_position = j["RobotPosition"];
    //     std::cout << robot_position[0];
        
    //     j_file.close();
        
        
    //     Manager m;
    //     MapInfo mpinfo(map_size, charge_station);
    //     Intruder intruder(&mpinfo);
    //     Robot states("default robot");
    //     Robot_Core core = Robot_Core(robot_name, &mpinfo, robot_position, battery_size, battery_consume_rate);

    //     m.schedule(intruder, 5_s)
    //         .schedule(states, 1_s)
    //         .schedule(core, 1_s)
    //         .init();
    //         m.run(60_s);
    // }
}