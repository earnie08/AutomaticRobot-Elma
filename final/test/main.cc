#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "elma.h"
#include "robot.h"
#include "battery.h"
#include "mapinfo.h"
using namespace std;

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Robot, Basic) {

    Manager m;

    Battery battery;
    MapInfo mapinfo(10);

    Robot robot("My Robot");

    m.schedule(battery, 10_ms)
      .schedule(mapinfo, 10_ms)
      .schedule(robot, 10_ms)
      .init()
      .start()
      .run(100_ms);

    // INSERT GRADING TESTS HERE 
}