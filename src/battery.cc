#include <iostream>
#include "battery.h"

namespace robot{
    Battery::Battery(){ 
        full_battery = 100;
        original_consume = 5;
        battery_status = full_battery;
        consume_value = original_consume;
    }
    
    Battery::Battery(int amount, int consumeRate){
        if(amount < 1 )
            amount = 100;
        
        if(consumeRate < 1)
            consumeRate = 5;

        full_battery = amount;
        battery_status = full_battery;
        original_consume = consumeRate;
        consume_value = original_consume;
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