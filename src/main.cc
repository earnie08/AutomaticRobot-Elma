#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>
#include "stopwatch.h"

#include "robot_core.h"
#include "robot_states.h"
#include "intruder.h"
#include "mapinfo.h"

using namespace std::chrono;
using namespace elma;
using namespace stopwatch;
using namespace robot;

int main() {
    /*
    Manager m;
    StopWatch stopwatch;
    UserInterface ui(stopwatch);

    m.schedule(ui, 10_ms)
     .schedule(stopwatch, 10_ms)     
     .init()
     .run();

    endwin();   
    */
    std::ifstream j_file("robot_setting.json");
    json j;
    j_file >> j;


    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n";
    }

    string robot_name = j["Robot Name"];
    std::cout << robot_name <<"\n";
    
    string mode = j["Mode"];
    std::cout << mode <<"\n";
    
    int map_size = j["MapSize"];
    std::cout << map_size << "\n";
    
    int battery_size = j["BatterySize"];
    int battery_consume_rate = j["BatteryConsumeRate"];
    vector<int> charge_station = j["ChargeStation"];
    vector<int> robot_position = j["RobotPosition"];
    std::cout << robot_position[0];
    
    j_file.close();
    
    
    Manager m;
    MapInfo mpinfo = MapInfo(map_size, charge_station);
    Intruder intruder = Intruder(&mpinfo);
    Robot_States states = Robot_States("default robot");
    Robot_Core core = Robot_Core(robot_name, &mpinfo, robot_position, battery_size, battery_consume_rate);

    m.schedule(intruder, 5_s)
        .schedule(states, 1_s)
        .schedule(core, 1_s)
        .init();
        m.run(60_s);
    
}  
