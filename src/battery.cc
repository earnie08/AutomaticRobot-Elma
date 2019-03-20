#include <iostream>
#include "battery.h"

namespace robot{
    Battery::Battery(){ 
        _fullBattery = 100;
        _originalConsume = 5;
        _batteryStatus = _fullBattery;
        _consumeValue = _originalConsume;
    }
    
    Battery::Battery(int amount, int consumeRate){
        _fullBattery = amount;
        _batteryStatus = _fullBattery;
        _originalConsume = consumeRate;
        _consumeValue = _originalConsume;
    }

    void Battery::consume(){
        _batteryStatus -= _consumeValue;
    }

    bool Battery::charge(){
        _batteryStatus += _consumeValue;
        if(_batteryStatus >= _fullBattery){
            _batteryStatus = _fullBattery;
            return false;
        }
        else
            return true;
    }
}