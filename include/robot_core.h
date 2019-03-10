#ifndef _ROBOT_CORE_H
#define _ROBOT_CORE_H

#include <iostream>
#include "elma.h"
#include "mapinfo.h"
#include "battery.h"

using namespace elma;
typedef enum {
    off,
    running,
    making_noise,
    evading,
    finding,
    charging
} Status;
class Robot_Core : public Process {
    public:
        Robot_Core(MapInfo *mpinfo) : Process("Robot Core") {
            mp_info = mpinfo;
            bool init = mp_info->setRobotLocation(0,0);
            status = off;
            proximity = false;
            noise = false;
            printStatus();
        }

        void init() {
            watch("start", [this](Event& e) {
                status = running;
            });

            watch("wandering",[this](Event& e){
                detecting();
                if(batteryRunOut()){
                    emit(Event("battery low"));
                    status = finding;
                }
                else{
                    wandering();
                    battery.consume();
                    printStatus();
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
                battery.setConsume(1);       
                pathToCharge();
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
            });

            watch("charging", [this](Event& e){
                if(battery.charge()){
                    emit(Event("battery full"));
                    printStatus();
                }
                std::cout << "Battery: " << battery.getStatus() << "\n\n";
            });

            watch("full", [this](Event& e) {
                status = running;
            });
        }

        void start() {}
        
        void update(){
            switch(status){
                case 1:
                    emit(Event("wandering"));
                    break;
                case 2:
                    detecting();
                    if(!noise) emit(Event("reset"));
                    break;
                case 3:
                    detecting();
                    if(!proximity) emit(Event("reset"));
                    else{
                        for(int i=0; i<2; i++){
                            if(batteryRunOut()){
                                emit(Event("battery low"));
                                status = finding;
                            }
                            else{
                                wandering();
                            }
                        }
                        battery.consume();
                        printStatus();
                    }
                    break;
                case 4:
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
        void stop(){}

        bool batteryRunOut(){
            int steps = abs(mp_info->getChargeStation().first - mp_info->getRobotPosition().first) + abs(mp_info->getChargeStation().second - mp_info->getRobotPosition().second);
            
            if(steps+1 >= battery.getStatus()/battery.getConsume()){
                std::cout << "Battery low...\n";
                return true;
            }
            else return false;
        }

        bool inChargeStation(){
            if(abs(mp_info->getChargeStation().first - mp_info->getRobotPosition().first) + abs(mp_info->getChargeStation().second - mp_info->getRobotPosition().second) == 0)
                return true;
            else return false;
        }

        void pathToCharge(){
            int x_steps = mp_info->getChargeStation().first - mp_info->getRobotPosition().first; // >0 right
            if(x_steps > 0){
                if(!mp_info->setRobotLocation(mp_info->getRobotPosition().first+1, mp_info->getRobotPosition().second))
                    std::cout << "somthing went wrong...\n"; 
            }
            else if (x_steps < 0){
                if(!mp_info->setRobotLocation(mp_info->getRobotPosition().first-1, mp_info->getRobotPosition().second))
                    std::cout << "somthing went wrong...\n"; 
            }
            else{
                int y_steps = mp_info->getChargeStation().second - mp_info->getRobotPosition().second; // >0 down
                if(y_steps > 0){
                    if(!mp_info->setRobotLocation(mp_info->getRobotPosition().first, mp_info->getRobotPosition().second+1))
                        std::cout << "somthing went wrong...\n"; 
                }
                else if(y_steps < 0)
                    if(!mp_info->setRobotLocation(mp_info->getRobotPosition().first, mp_info->getRobotPosition().second-1))
                        std::cout << "somthing went wrong...\n"; 
            }
        }

        void wandering(){
            bool end = false;
            int pos_x = mp_info->getRobotPosition().first;
            int pos_y = mp_info->getRobotPosition().second;

            while(!end){
                int direction = rand() % 4 + 1;
                cout << "Direction: " << direction << "\n";
                /*switch(direction){
                    case 1: 
                        end = setRobotLocation(pos_x-1, pos_y-1);
                        break;
                    case 2:
                        end = setRobotLocation(pos_x-1, pos_y);
                        break;
                    case 3:
                        end = setRobotLocation(pos_x-1, pos_y+1);
                        break;
                    case 4:
                        end = setRobotLocation(pos_x, pos_y-1);
                        break;
                    case 5:
                        continue;
                    case 6:
                        end = setRobotLocation(pos_x, pos_y+1);
                        break;
                    case 7:
                        end = setRobotLocation(pos_x+1, pos_y-1);
                        break;
                    case 8:
                        end = setRobotLocation(pos_x+1, pos_y);
                        break;
                    case 9:
                        end = setRobotLocation(pos_x+1, pos_y+1);
                        break;
                }*/
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

        void detecting(){
            int I_x = mp_info->getIntruderPosition().first;
            int I_y = mp_info->getIntruderPosition().second;
            int R_x = mp_info->getRobotPosition().first;
            int R_y = mp_info->getRobotPosition().second;

            if(abs(R_x - I_x) <= 4 && abs(R_y - I_y) <=4 ){
                std::cout << "Intruder Position: " << R_x << "," << R_y << "\n";
                emit(Event("intruder detected"));
                noise = true;
            } else noise = false;

            if(abs(R_x - I_x) <= 2 && abs(R_y - I_y) <=2){
                emit(Event("proximity warning"));
                proximity = true;
            } else proximity = false;
        }

    private:
        Status status;
        bool noise, proximity;
        Battery battery;
        MapInfo *mp_info;

        void printStatus(){
            mp_info->printMap();
            std::cout << "Current Position: " << mp_info->getRobotPosition().first << "," << mp_info->getRobotPosition().second << "\n";
            std::cout << "Charge Station: " << mp_info->getChargeStation().first << "," << mp_info->getChargeStation().second << "\n";
            std::cout << "Battery: " << battery.getStatus() << "   Consume: " << battery.getConsume() << "\n";
            std::cout << "Battery Consume Rate: " << battery.getConsume() << "\n\n";
        }
};
#endif