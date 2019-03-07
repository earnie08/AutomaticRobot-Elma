#ifndef _BATTERY_H
#define _BATTERY_H

#include <iostream>
using namespace std;


class Battery{
    public:
    //! Default construct
    Battery(){ 
        battery_status = 100;
        consume_value = 10;
    }
    
    Battery(int amount){
        battery_status = amount;
        consume_value = amount/10;
    }

    //! Overwrite process interface
    void consume(){
        battery_status -= consume_value;
    }

    void charge(){
        battery_status += consume_value;
    }

    void setConsume(int value) { consume_value = value; }
    double getBattery() { return battery_status; }
    double getConsume() { return consume_value; }

    private:
        double battery_status, consume_value;
};

#endif