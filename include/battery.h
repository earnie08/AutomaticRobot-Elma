#ifndef _BATTERY_H
#define _BATTERY_H

#include <iostream>
using namespace std;


class Battery{
    public:
    //! Default construct
    Battery(){ 
        
        full_battery = 200;
        battery_status = full_battery;
        consume_value = 10;
        std::cout << "Set robot batter: " << full_battery << " comsume: " << consume_value << " per times.\n\n";
    }
    
    Battery(int amount){
        full_battery = amount;
        battery_status = full_battery;
        consume_value = amount/10;
    }

    //! Overwrite process interface
    void consume(){
        battery_status -= consume_value;
    }

    bool charge(){
        battery_status += consume_value;
        if(battery_status >= full_battery)
            return true;
        else
            return false;
    }

    void setConsume(int value) { consume_value = value; }
    double getBattery() { return full_battery; }
    double getStatus() { return battery_status; }
    double getConsume() { return consume_value; }

    private:
        double full_battery, battery_status, consume_value;
};

#endif