#include "setting.h"

using namespace robot;

Setting::Setting(json j){
    try{
        name = j["Robot Name"];
        mapsize = j["Map Size"];
        amount = j["Battery Size"];
        rate = j["Battery Consume Rate"];
        vector<int> charg_station = j["Charge Station"];
        vector<int> robot_pos = j["Robot Position"];

        station = charg_station;
        robot = robot_pos;

        detection_area = j["Robot Detection Area"];
        proximity_area = j["Robot Proximity Area"];

        if(!checkCustomizeSetting())
            throw std::range_error("Customize setting value is out of range");
    }
    catch(const json::exception& e ) {
        std::cout << "Json exception: " << e.what() << "\n";
    }
}

void Setting::runRobot(){
    Manager m;
    MapInfo map(mapsize, station, robot);
    Intruder intruder(map);
    Battery battery(amount, rate);
    Robot robot(name, &map, &battery, detection_area, proximity_area);
    RobotInterface ui(robot, map, getSetting());

    m.schedule(intruder, 5_s)
     .schedule(robot, 1_s)
     .schedule(ui, 1_s)
     .init()
     .run();
}

bool Setting::checkCustomizeSetting(){
    //best for visualizing
    if(mapsize > 20 || mapsize < 5){
        cout << "Map size is out of visualization\n";
        return false;
    }
    //consume rate is too high, robot can't go back to recharge in time
    // rate*2 --> consume rate will be 2x times when evading 
    else if(rate > amount || amount/(rate*2) <= abs(station[0]-robot[0]) + abs(station[1]/robot[1])){
        cout << "robot can't go back to recharge in time\n";
        return false;
    }
    //station or robot position is out of array
    else if(station[0] > mapsize-1 || station[0] < 0 || station[1] > mapsize-1 || station[1] < 0
     || robot[0] > mapsize-1 || robot[0] < 0 || robot[1] > mapsize-1 || robot[1] < 0
     || (station[0] == robot[0] && station[1] == robot[1])){
        cout << "station or robot position is out of array\n";
        return false;
    }

    else if(detection_area > mapsize || detection_area < 1){
        cout << "detection area is out of array\n";
        return false;
    }
    
    else if(proximity_area > detection_area || proximity_area > mapsize){
        cout << "detection area is out of array\n";
        return false;
    }
    else return true;
}

vector<string> Setting::getSetting(){
    vector<string> v;

    v.push_back("Customize Setting Info:");
    v.push_back("Robot Name: " + name);
    v.push_back("Map Size: " + to_string(mapsize));
    v.push_back("Battery Size: " + to_string(amount));
    v.push_back("Battery Consume Rate: " + to_string(rate));
    v.push_back("Charge Station Position: [" + to_string(station[0]) + "," + to_string(station[1]));
    v.push_back("Robot Intruder Detection Area: " + to_string(detection_area) + "x" + to_string(detection_area));
    v.push_back("Robot Proximity Detection Area: " + to_string(proximity_area) + "x" + to_string(proximity_area));
    return v;
}