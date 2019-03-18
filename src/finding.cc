#include <iostream>
#include "robot.h"

using namespace elma;
using namespace robot;

Robot&Finding:: robot() { return (Robot&) state_machine(); }

void Finding::entry(const Event& e) {
    robot().setStatus(finding_station);
}

void Finding::during() {
    if(inChargeStation()){
        emit(Event("found charge station"));
    }
    else{
        robot().getBattery()->consume();
    }
}

void Finding::exit(const Event& e) {
    robot().getBattery()->consume();
    robot().getMap()->cleanMap();
}

/*
    Logic:
        x first: go down/up first until x position equal to charge station
            If Intruder is in my next direction(down or up) to charge station
            . robot will go one step left/right (depends on wherer is charge stattion).

            If Intruder is in my next direction(down or up) and charge station is in the same vertical line
            . robot will go one step left/right and change the priority to y-axis first (left/right first).
        
        y-axis first: go right/left first, same logic as x-axis first
*/
bool Finding::inChargeStation(){
    auto mp_info = robot().getMap();

    int r_x_pos = mp_info->getRobotPosition().first;
    int r_y_pos = mp_info->getRobotPosition().second;

    int i_x_pos = mp_info->getIntruderPosition().first;
    int i_y_pos = mp_info->getIntruderPosition().second;

    int x_steps = mp_info->getChargeStation().first - r_x_pos;
    int y_steps = mp_info->getChargeStation().second - r_y_pos;
    
    if((x_steps == 0 && abs(y_steps) == 1) || (abs(x_steps) == 1 && y_steps == 0)){
        x_first = true;
        return true;
    }

    if(x_first){
        if(x_steps != 0){
            if(r_x_pos + x_steps/abs(x_steps) == i_x_pos && r_y_pos == i_y_pos){
                    if(y_steps != 0)
                        mp_info->setRobotLocation(r_x_pos, r_y_pos + y_steps/abs(y_steps));
                    else{
                        if(r_y_pos + 1 >= (mp_info->getMapSize()-1)/2 || mp_info->getMap()[r_x_pos][r_y_pos + 1] != ' ')
                            mp_info->setRobotLocation(r_x_pos, r_y_pos - 1);
                        else mp_info->setRobotLocation(r_x_pos, r_y_pos + 1);
                        x_first = true;
                    }
            }
            else mp_info->setRobotLocation(r_x_pos + x_steps/abs(x_steps), r_y_pos);
        }
        else{
            if(r_y_pos + y_steps/abs(y_steps) == i_y_pos && r_x_pos == i_x_pos){
                    if(x_steps != 0)
                        mp_info->setRobotLocation(r_x_pos + x_steps/abs(x_steps), r_y_pos);
                    else{
                        if(r_x_pos + 1 >= (mp_info->getMapSize()-1)/2 || mp_info->getMap()[r_x_pos + 1][r_y_pos] != ' ')
                            mp_info->setRobotLocation(r_x_pos - 1, r_y_pos);
                        else mp_info->setRobotLocation(r_x_pos + 1, r_y_pos);
                        x_first = false;
                    }
            }
            else mp_info->setRobotLocation(r_x_pos, r_y_pos + y_steps/abs(y_steps));
        }
    }
    else{
        if(y_steps != 0){
            if(r_y_pos + y_steps/abs(y_steps) == i_y_pos && r_x_pos == i_x_pos){
                    if(x_steps != 0)
                        mp_info->setRobotLocation(r_x_pos + x_steps/abs(x_steps), r_y_pos);
                    else{
                        if(r_x_pos + 1 >= (mp_info->getMapSize()-1)/2 || mp_info->getMap()[r_x_pos + 1][r_y_pos] != ' ')
                            mp_info->setRobotLocation(r_x_pos - 1, r_y_pos);
                        else mp_info->setRobotLocation(r_x_pos + 1, r_y_pos);
                        x_first = false;
                    }
            }
            else mp_info->setRobotLocation(r_x_pos, r_y_pos + y_steps/abs(y_steps));
        }
        else{
            if(r_x_pos + x_steps/abs(x_steps) == i_x_pos && r_y_pos == i_y_pos){
                    if(y_steps != 0)
                        mp_info->setRobotLocation(r_x_pos, r_y_pos + y_steps/abs(y_steps));
                    else{
                        if(r_y_pos + 1 >= (mp_info->getMapSize()-1)/2 || mp_info->getMap()[r_x_pos][r_y_pos + 1] != ' ')
                            mp_info->setRobotLocation(r_x_pos, r_y_pos - 1);
                        else mp_info->setRobotLocation(r_x_pos, r_y_pos + 1);
                        x_first = true;
                    }
            }
            else mp_info->setRobotLocation(r_x_pos + x_steps/abs(x_steps), r_y_pos);
        }
    }
    return false;
}