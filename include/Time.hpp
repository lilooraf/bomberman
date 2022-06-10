/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TIME
*/

#include "defs.hpp"
#include "Core.hpp"

#ifndef TIME_HPP_
#define TIME_HPP_

class Time {
    public:
        Time();
        ~Time();
        void startTime();
        int getTimeSecond() const;
        std::string getTime();
        void resetTime();
        void startTimeClock();
        void stopClock();
        void stopTime();
        void setDevice(irr::IrrlichtDevice *device);
        void setCore(Core *core);
        void printCLock();
        void stopAll();
    protected:
    private:
        int _time;
        bool _stop_clock;
        bool _stop_time;
        bool _first;
        irr::IrrlichtDevice *_device;
        irr::gui::IGUIStaticText *_text;
        Core *_core;
};

#endif /* !TIME_HPP_ */
