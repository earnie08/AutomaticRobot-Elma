#ifndef _ROBOT_H
#define _ROBOT_H

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
    }
    void during() {
        emit(Event("Print Map"));
    } 
    void exit(const Event& e) {
        cout << "Wander Exit: "<< e.name() << "\n";
    }
};

class MakeNoise : public State {
    public:
    MakeNoise() : State("Make Noise") {}
    void entry(const Event& e) {
        cout << "Make Noise Enter: "<< e.name() << "\n";
        if(e.name() == "intruder dected")
            emit(Event("intruder"));
    }
    void during() {} 
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
    FindRechargeStation() : State("FindRechargeStation") {}
    void entry(const Event& e) {
        cout << "Find Recharge Station Enter...\n";
        cout << "Close proximity and noise warning...\n";
        emit(Event("reset proximity"));
        emit(Event("reset noise"));
    }
    void during() {
        cout << "Finding recharge station...\n";
    } 
    void exit(const Event& e) {
        cout << "Find Recharge Station Exit:\n";
        emit(Event("found station"));
    }
};

class Recharge : public State {
    public:
    Recharge() : State("Recharge") {}
    void entry(const Event& e) {
        cout << "Recharge Enter...\n";
    }
    void during() {
        cout << "Recharging...\n";
    } 
    void exit(const Event& e) {
        cout << "Recharge Exit: " << e.name() << "\n";
        if(e.name() == "battery full")
            emit(Event("full"));
    }
};

class Robot : public StateMachine {
public:
    Robot(std::string name) : StateMachine(name) {
        set_initial(wander);
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
    Wander wander;
    MakeNoise makenoise;
    Evade evade;
    FindRechargeStation find_recharge_station;
    Recharge recharge;
};

#endif