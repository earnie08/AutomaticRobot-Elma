#ifndef _ROBOT_CORE_H
#define _ROBOT_CORE_H


#include <iostream>
#include "elma.h"
#include "mapinfo.h"
#include "battery.h"

using namespace elma;

class Robot_Core : public Process {
    public:
        Robot_Core(MapInfo mpinfo) : Process("Robot Core") {
            mp_info = mpinfo;
            running = false;
            charging = false;
        }

        void init() {
            watch("start", [this](Event& e) {
                running = true;
            });

            watch("wandering",[this](Event& e){
                if(batteryRunOut().first){
                    emit(Event("battery low"));
                }
                else{
                    wandering();
                    mp_info.printMap();
                }
            });

            watch("intruder", [this](Event& e) {
                battery.setConsume(battery.getConsume() + 10);
            });
        
            watch("reset noise", [this](Event& e) {
                battery.setConsume(battery.getConsume() - 10);
            });

            watch("proximity", [this](Event& e) {
                battery.setConsume(battery.getConsume() + 10);
            });

            watch("reset proximity", [this](Event& e) {
                battery.setConsume(battery.getConsume() - 10);
            });

            watch("found station", [this](Event& e) {
                running = false;
                charging = true;
            });

            watch("finding station", [this](Event& e) {
                //batteryRunout().second
            });

            watch("full", [this](Event& e) {
                running = true;
                charging = false;
            });
            
        }

        void start() {}
        void update(){
            if(running){
                battery.consume();
                emit(Event("wandering"));
            }

            if(charging && !running){
                emit(Event("charging"));
            }
/*
            if (battery.getStatus() <= 20 && !charging){
                emit(Event("battery low"));
            }

            if (battery.getStatus() == 100 && charging){
                emit(Event("full"));
            }

            if(battery.getStatus() == 0){
                std::cout << "Robot out of battery. Shutting down...\n";
                running = false;
            }        
*/ 
        }
        void stop(){}

        pair<bool,int> batteryRunOut(){
            int steps = abs(mp_info.getChargeStation().first - mp_info.getPosition().first) + abs(mp_info.getChargeStation().second - mp_info.getPosition().second);

            std::cout << "Current Position: " << mp_info.getPosition().first << "," << mp_info.getPosition().second << "\n";
            std::cout << "Charge Station: " << mp_info.getChargeStation().first << "," << mp_info.getChargeStation().second << "\n";
            std::cout << "steps: " << steps << "\n";
            std::cout << "steps to charge: " << battery.getBattery()/battery.getConsume() << "\n";

            if((steps-1) <= battery.getBattery()/battery.getConsume()){
                std::cout << "Battery low...\n";
                return make_pair(true,steps);
            }
            else return make_pair(false, 0);
        }

        void wandering(){
            bool end = false;
            int pos_x = mp_info.getPosition().first;
            int pos_y = mp_info.getPosition().second;

            while(!end){
                int direction = rand() % 4 + 1;
                cout << "Direction: " << direction << "\n\n";
                /*switch(direction){
                    case 1: 
                        end = setRoute(pos_x-1, pos_y-1);
                        break;
                    case 2:
                        end = setRoute(pos_x-1, pos_y);
                        break;
                    case 3:
                        end = setRoute(pos_x-1, pos_y+1);
                        break;
                    case 4:
                        end = setRoute(pos_x, pos_y-1);
                        break;
                    case 5:
                        continue;
                    case 6:
                        end = setRoute(pos_x, pos_y+1);
                        break;
                    case 7:
                        end = setRoute(pos_x+1, pos_y-1);
                        break;
                    case 8:
                        end = setRoute(pos_x+1, pos_y);
                        break;
                    case 9:
                        end = setRoute(pos_x+1, pos_y+1);
                        break;
                }*/
                switch(direction){
                    case 1:
                        end = mp_info.setRoute(pos_x-1, pos_y);
                        break;
                    case 2:
                        end = mp_info.setRoute(pos_x, pos_y-1);
                        break;
                    case 3:
                        end = mp_info.setRoute(pos_x, pos_y+1);
                        break;
                    case 4:
                        end = mp_info.setRoute(pos_x+1, pos_y);
                        break;
                }
            }
            mp_info.cleanRoute(pos_x,pos_y);
        }
    private:
        bool running, charging;
        MapInfo mp_info;
        Battery battery;
};
#endif