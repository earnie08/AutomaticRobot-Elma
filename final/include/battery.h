#ifndef _BATTERY_H
#define _BATTERY_H


#include <iostream>
#include "elma.h"
using namespace elma;

class Battery : public Process {

    public:
    Battery() : Process("bettery") {}
    void init() {
        watch("found station", [this](Event& e) {
            running = false;
            charging = true;
        });

        watch("start", [this](Event& e) {
            running = true;
        });
        
        watch("intruder", [this](Event& e) {
            battery_consuming += 10;
        });
        watch("reset noise", [this](Event& e) {
            battery_consuming -= 10;
        });

        watch("proximity", [this](Event& e) {
            battery_consuming += 10;
        });
        watch("reset proximity", [this](Event& e) {
            battery_consuming -= 10;
        });

        watch("full", [this](Event& e) {
            running = true;
            charging = false;
        });
    }

    void start() {
        running = false;
        charging = false;
        battery_status= 100;
        battery_consuming = 10;
    }

    void update() {
        //battery -10 every update
        if(running)
            battery_status -= battery_consuming;
        if(charging && !running){
            battery_status += 10;
            std::cout << "Battery Status:" << battery_status << "\n";
        }
        if (battery_status <= 20 && !charging){
            emit(Event("battery low"));
        }

        if (battery_status == 100 && charging){
            emit(Event("battery full"));
        }

        if(battery_status == 0){
            std::cout << "Robot out of battery. Shutting down...\n";
            running = false;
        }
        
        std::cout << "Battery state: " << battery_status << "\n\n";
        
    }
    void stop() {}

    int getBatteryStatus() { return battery_status; }
    bool getRunning() { return running; }
    bool getCharging() { return charging; }

    private:
        bool running, charging;
        int battery_status, battery_consuming;

};

#endif