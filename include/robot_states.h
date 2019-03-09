#ifndef _ROBOT_STATES_H
#define _ROBOT_STATES_H

#include <iostream>
#include <chrono>
#include "gtest/gtest.h"
#include "elma.h"
using namespace elma;
using namespace std;

//! \file
class Wander : public State {
    public:
    Wander() : State("Wander") {}
    void entry(const Event& e) {
        cout << "Wander Enter: "<< e.name() << "\n";
        if(e.name() == "start robot")
            emit(Event("start"));
    }
    void during() {} 
    void exit(const Event& e) {
        cout << "Wander Exit: "<< e.name() << "\n";
    }
};

class MakeNoise : public State {
    public:
    MakeNoise() : State("Make Noise") {}
    void entry(const Event& e) {
        cout << "Make Noise Enter: "<< e.name() << "\n";
        if(e.name() == "intruder detected")
            emit(Event("intruder"));
    }
    void during() { cout << "Intruder Detected!!!!\n"; } 
    void exit(const Event& e) {
        cout << "Make Noise Exit: "<< e.name() << "\n";
        if(e.name() == "reset")
            emit(Event("reset noise"));
    }
};

class Evade : public State {
    public:
    Evade() : State("Evade") {}
    void entry(const Event& e) {
        cout << "Evade Enter: " << e.name() << "\n";
        if(e.name() == "proximity warning"){
            emit(Event("proximity"));
        }
    }
    void during() {
        cout << "Proximity Warning!!!!\n";
    } 
    void exit(const Event& e) {
        cout << "Evade Exit: " << e.name() << "\n";
        if(e.name() == "reset")
            emit(Event("reset evade"));
    }
};

class FindRechargeStation : public State {
    public:
    FindRechargeStation() : State("Find Recharge Station") {}
    void entry(const Event& e) {
        cout << "Finding Recharge Station Enter...\n";
        cout << "Close proximity and noise warning...\n";
        emit(Event("reset proximity"));
        emit(Event("reset noise"));
    }
    void during() {
        cout << "Finding recharge station...\n";
    } 
    void exit(const Event& e) {
        cout << "Found Recharge Station Exit\n";
    }
};

class Recharge : public State {
    public:
    Recharge() : State("Recharge") {}
    void entry(const Event& e) {
        cout << "Recharge Enter...\n";
        emit(Event("found station"));
    }
    void during() {
        cout << "Recharging...\n";
    } 
    void exit(const Event& e) {
        cout << "Battery Full\nRecharge Station Exit\n\n";
        if(e.name() == "battery full")
            emit(Event("full"));
    }
};

class Off: public State {
    public:
    Off() : State("Off"){}
    void entry(const Event& e){ emit(Event("start robot")); }
    void during(){}
    void exit(const Event& e){}
};

class Robot_States : public StateMachine {
public:
    Robot_States() : StateMachine("Default Machine") {}
    Robot_States(string name) : StateMachine(name) {
        set_initial(off);
        add_transition("start robot", off, wander);
        add_transition("intruder detected", wander, makenoise);
        add_transition("battery low", wander, find_recharge_station);

        add_transition("proximity warning", makenoise, evade);
        add_transition("reset", makenoise, wander);

        add_transition("reset", evade, makenoise);
        add_transition("battery low", evade, find_recharge_station);

        add_transition("found recharge station", find_recharge_station, recharge);

        add_transition("battery full", recharge, wander);
    }

private:
    Off off;
    Wander wander;
    MakeNoise makenoise;
    Evade evade;
    FindRechargeStation find_recharge_station;
    Recharge recharge;
};

#endif