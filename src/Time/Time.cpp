/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Time
*/

#include "Time.hpp"

Time::Time()
{
    this->_time = 0;
    this->_stop_clock = false;
    this->_stop_time = false;
    this->_first = true;
}

Time::~Time()
{
    this->_stop_clock = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    this->_stop_time = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Time::startTime()
{
    this->_stop_time = true;
    if (this->_stop_clock == false)
        startTimeClock();
    std::thread thread = std::thread([&]() {
        for (int i = 0; this->_stop_time && this->_core->isGameRunning(); i++) {
            if (i == 999) {
                this->_time += 1;
                i = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
    thread.detach();
}

int Time::getTimeSecond() const
{
    return this->_time;
}

void Time::resetTime()
{
    this->_time = 0;
    this->_stop_time = true;
    startTime();
}

std::string Time::getTime()
{
    int second_time = getTimeSecond();
    int min = second_time / 60;
    int second = second_time % 60;

    std::string str_second = std::to_string(second);
    std::string str_min = std::to_string(min);
    std::string time = str_min;

    if (str_min.length() == 0)
        time = "00";
    if (str_min.length() == 1)
        time = "0" + time;
    if (str_second.length() == 1)
        time = time + "     0" + str_second;
    else
        time = time + "     " + str_second; 
    return (time);
}

void Time::stopClock()
{
    this->_stop_clock = false;
}

void Time::stopTime()
{
    this->_stop_time = false;
}

void Time::stopAll()
{
    stopClock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    stopTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Time::setDevice(irr::IrrlichtDevice *device)
{
    this->_device = device;
}

void Time::setCore(Core *core)
{
    this->_core = core;
}

void Time::startTimeClock()
{
    std::string time = getTime();
    std::wstring widestr = std::wstring(time.begin(), time.end());
    if (this->_first == true) {
        this->_text = this->_device->getGUIEnvironment()->addStaticText(widestr.c_str(), irr::core::rect<irr::s32>(130,20,300,60));
    }
    this->_stop_clock = true;
    std::thread thread = std::thread([&]() {
        for (int i = 0; this->_stop_clock && this->_core->isGameRunning(); i++) {
            if (i == 99) {
                printCLock();
                i = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
    thread.detach();
}

void Time::printCLock()
{
    if (this->_first == true) {
        this->_text->setOverrideFont(this->_core->getWindow()->getFont28());
        this->_text->setRelativePosition(irr::core::position2d<irr::s32>(902,40));
        this->_text->setOverrideColor(irr::video::SColor(255,255,255,255));
        this->_first = false;
    }
    std::string time = getTime();
    std::wstring widestr = std::wstring(time.begin(), time.end());
    this->_text->setText(widestr.c_str());
}