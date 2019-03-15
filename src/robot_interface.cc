#include <unistd.h>
#include "robot_interface.h"

using namespace robot;

RobotInterface::RobotInterface(Robot_Core& rc) : Process("Robot Interface"){
    initscr();
    timeout(1);
    noecho();
    curs_set(0);
}

void RobotInterface::update(){

}