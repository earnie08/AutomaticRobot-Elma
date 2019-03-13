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
    Robot_States states = Robot_States("default robot");
    Robot_Core core = Robot_Core(&mp_info);

    m.schedule(states, 1_s)
     .schedule(intruder, 5_s)
     .schedule(core, 1_s)
     .init();
    m.run(60_s);
}