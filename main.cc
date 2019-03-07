#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "elma.h"
#include "robot_core.h"
#include "robot_states.h"

using namespace std;

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Robot, Basic) {
    Manager m;
    MapInfo mp_info = MapInfo(10);
    Robot_States states = Robot_States("default robot");
    Robot_Core core = Robot_Core(mp_info);

    m.schedule(core, 10_ms)
     .schedule(states, 10_ms)
     .init();
    
    m.run(100_ms);
}