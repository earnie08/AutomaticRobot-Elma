#include <iostream>
#include "robot_core.h"

namespace robot{
    Robot_Core::Robot_Core(MapInfo *mpinfo):Process("Default Robot"){
        mp_info = mpinfo;
        mp_info->setRobotLocation(0,0);
        status = off;
        proximity = false;
        noise = false;
        x_first = true;
        printStatus();
    }
    
    Robot_Core::Robot_Core(string robotName, MapInfo *mpinfo, vector<int> robotPosition, int batterySize, int consumeRate) : Process(robotName){
        mp_info = mpinfo;
        mp_info->setRobotLocation(robotPosition[0],robotPosition[1]);

        battery = Battery(batterySize, consumeRate);
        status = off;
        proximity = false;
        noise = false;
        x_first = true;
        printStatus();
    }

    void Robot_Core::wandering(){
        bool end = false;
        int pos_x = mp_info->getRobotPosition().first;
        int pos_y = mp_info->getRobotPosition().second;

        while(!end){
            int direction = rand() % 4 + 1;
            cout << "Direction: " << direction << "\n";
            switch(direction){
                case 1:
                    end = mp_info->setRobotLocation(pos_x-1, pos_y);
                    break;
                case 2:
                    end = mp_info->setRobotLocation(pos_x, pos_y-1);
                    break;
                case 3:
                    end = mp_info->setRobotLocation(pos_x, pos_y+1);
                    break;
                case 4:
                    end = mp_info->setRobotLocation(pos_x+1, pos_y);
                    break;
            }
        }
        if(pos_x !=mp_info->getChargeStation().first || pos_y != mp_info->getChargeStation().second)
            mp_info->cleanSymbol(pos_x,pos_y);
    }

    bool Robot_Core::batteryRunOut(){
        int steps = abs(mp_info->getChargeStation().first - mp_info->getRobotPosition().first) + abs(mp_info->getChargeStation().second - mp_info->getRobotPosition().second);
        
        if(steps+1 >= battery.getStatus()/battery.getConsume()){
            std::cout << "Battery low...\n";
            return true;
        }
        else return false;
    }

    /*
    Logic:
        x first: go down/up first until x position equal to charge station
            If Intruder is in my next direction(down or up) to charge station
            -> robot will go one step left/right (depends on wherer is charge stattion).

            If Intruder is in my next direction(down or up) and charge station is in the same vertical line
            -> robot will go one step left/right and change the priority to y-axis first (left/right first).
        
        y-axis first: go right/left first, same logic as x-axis first
    */
    bool Robot_Core::inChargeStation(){
        int r_x_pos = mp_info->getRobotPosition().first;
        int r_y_pos = mp_info->getRobotPosition().second;

        int c_x_pos = mp_info->getChargeStation().first;
        int c_y_pos = mp_info->getChargeStation().second;

        int i_x_pos = mp_info->getIntruderPosition().first;
        int i_y_pos = mp_info->getIntruderPosition().second;

        int x_steps = (c_x_pos - r_x_pos);
        int y_steps = (c_y_pos - r_y_pos);

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

    bool Robot_Core::detecting(){
        int I_x = mp_info->getIntruderPosition().first;
        int I_y = mp_info->getIntruderPosition().second;
        int R_x = mp_info->getRobotPosition().first;
        int R_y = mp_info->getRobotPosition().second;

        if(abs(R_x - I_x) <= 4 && abs(R_y - I_y) <=4){
            if(!noise){
                noise = true;
                std::cout << "Intruder Position: " << I_x << "," << I_y << "\n";
                emit(Event("intruder detected"));
            }
        } else noise = false;

        if(!proximity && abs(R_x - I_x) <= 2 && abs(R_y - I_y) <=2){
            if(!proximity){
                proximity = true;
                emit(Event("proximity warning"));
            }
        } else proximity = false;

        if(noise || proximity) return true;
        if(!noise && !proximity) return false;
    }

    void Robot_Core::init() {
        watch("start", [this](Event& e) {
            status = running;
        });

        watch("wandering",[this](Event& e){
            if(!detecting()){
                if(batteryRunOut()){
                    emit(Event("battery low"));
                    status = finding;
                }
                else{
                    wandering();
                    battery.consume();
                    printStatus();
                }
            }
        });

        watch("intruder", [this](Event& e) {
            battery.setConsume(5);
            status = making_noise;
        });

        watch("reset noise", [this](Event& e) {
            if(noise){
                battery.setConsume(battery.getBattery() / 10);
                status = running;
            }
        });

        watch("proximity", [this](Event& e) {
            battery.setConsume((battery.getConsume() + 10));
            status = evading;
        });

        watch("reset proximity", [this](Event& e) {
            if(proximity){
                battery.setConsume(battery.getBattery() / 10);
                status = running;
            }
        });

        watch("finding station", [this](Event& e) { 
            battery.setConsume(5);       

            if(inChargeStation()){
                battery.consume();
                mp_info->cleanMap();
                emit(Event("found recharge station"));
            }
            else {
                battery.consume();
            }
            printStatus();
        });

        watch("found station", [this](Event& e) {
            status = charging;
            battery.setConsume(10);  
        });

        watch("charging", [this](Event& e){
            if(!battery.charge()){
                mp_info->setRobotLocation(mp_info->getRobotPosition().first, mp_info->getRobotPosition().second);
                printStatus();
                emit(Event("battery full"));
            }
            else std::cout << "Battery: " << battery.getStatus() << "\n\n";
        });

        watch("full", [this](Event& e) {
            status = running;
        });
    }

    void Robot_Core::update(){
        /*
            off = 0
            running = 1
            making_noise = 2
            evading = 3
            finding = 4
            charging = 5
        */
        switch(status){
            case 1:
                emit(Event("wandering"));
                break;
            case 2:
                if(!detecting())
                    emit(Event("reset"));
                else {
                    cout << "Intruder Detected!!!!\nRobot Stop and make noise!!!!\n";
                    printStatus();
                }
                break;
            case 3:
                if(!detecting())
                    emit(Event("reset"));
                else{
                    cout << "Proximity Warning!!!!\n";
                    for(int i=0; i<2; i++){
                        if(batteryRunOut()){
                            emit(Event("battery low"));
                            status = finding;
                        }
                        else{
                            wandering();
                            battery.consume();
                        }
                    }
                    printStatus();
                }
                break;
            case 4:
                noise = false;
                proximity = false;
                emit(Event("finding station"));
                break;
            case 5:
                emit(Event("charging"));
                break;
            default: 
                std::cout << "Robot update error in status: " << status << "\n";
                status = off;
                break;
        }
    }

    void Robot_Core::printStatus(){
        mp_info->printMap();
        std::cout << "Current Position: " << mp_info->getRobotPosition().first << "," << mp_info->getRobotPosition().second << "\n";
        std::cout << "Charge Station: " << mp_info->getChargeStation().first << "," << mp_info->getChargeStation().second << "\n";
        std::cout << "Battery: " << battery.getStatus() << "\n";
        std::cout << "Battery Consume Rate: " << battery.getConsume() << "\n\n";
    }
}
