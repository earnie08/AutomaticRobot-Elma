#include <iostream>
#include "battery.h"

namespace robot{
    Battery::Battery(){ 
        full_battery = 100;
        battery_status = full_battery;
        consume_value = 5;
    }
    
    Battery::Battery(int amount, int consumeRate){
        if(amount <=0 )
            amount = 100;
   
        full_battery = amount;
        battery_status = full_battery;
        consume_value = consumeRate;
    }

    void Battery::consume(){
        battery_status -= consume_value;
    }

    bool Battery::charge(){
        battery_status += consume_value;
        if(battery_status >= full_battery){
            battery_status = full_battery;
            return false;
        }
        else
            return true;
    }
}