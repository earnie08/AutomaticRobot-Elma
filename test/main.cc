#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "elma.h"
#include "robot_core.h"
#include "robot_states.h"
#include "intruder.h"
#include "mapinfo.h"

using namespace std;

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Robot, Basic) {
    Manager m;
    MapInfo mp_info = MapInfo(10);
    Intruder intruder = Intruder(&mp_info);
    mp_info.printMap();
    Robot_States states = Robot_States("default robot");
    Robot_Core core = Robot_Core(&mp_info);
    mp_info.printMap();

    m.schedule(states, 10_ms)
     .schedule(intruder, 50_ms)
     .schedule(core, 10_ms)
     .init();
    //m.run(350_ms);
}