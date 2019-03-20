#ifndef _BATTERY_H
#define _BATTERY_H

#include <iostream>
using namespace std;

namespace robot{
    class Battery{
        public:
        //! Default construct
        Battery();

        //! Customize Battery construct. Amount will automatically set to 100 if input amount <= 0,
        //! \param amount The amount of battery.
        //! \param consume_rate The consume rate of battery.
        Battery(int amount, int consumeRate);

        //! Battery consume function
        void consume();

        //! Battery charging function
        //! \return Ture: charging ; False: battery is full
        bool charge();

        inline void setConsume(double value) { _consumeValue = value; }
        inline double getBattery() { return _fullBattery; }
        inline double getConsumeRate(){ return _originalConsume; }
        inline double getStatus() { return _batteryStatus; }
        inline double getConsume() { return _consumeValue; }

        private:
            double _fullBattery, _batteryStatus, _consumeValue, _originalConsume;
    };
}

#endif