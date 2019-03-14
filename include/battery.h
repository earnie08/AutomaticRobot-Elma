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
        Battery(int amount, int consume_rate);

        //! Battery consume function
        void consume();

        //! Battery charging function
        //! \return Ture: charging ; False: battery is full
        bool charge();

        inline void setConsume(int value) { consume_value = value; }
        inline double getBattery() { return full_battery; }
        inline double getStatus() { return battery_status; }
        inline double getConsume() { return consume_value; }

        private:
            double full_battery, battery_status, consume_value;
    };
}

#endif