/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EventManager
*/

#include "EventManager.hpp"

EventManager::EventManager()
{
    this->_w = true;
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++) {
        this->KeyIsDown.push_back(false);
        this->KeyIsPressed.push_back(false);
    }
}

EventManager::~EventManager()
{
    this->KeyIsDown.clear();
    this->KeyIsPressed.clear();
}

bool EventManager::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        if (event.KeyInput.PressedDown && !KeyIsDown[event.KeyInput.Key])
            KeyIsPressed[event.KeyInput.Key] = true;
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    return (false);
}

bool EventManager::IsKeyPressed(irr::EKEY_CODE keyCode) const
{
    return (KeyIsPressed[keyCode]);
}

/* 
bool EventManager::IsKeyDownGame(irr::EKEY_CODE keyCode) const
{
    if (KeyIsDown[keyCode]) {
        return true;
    } else
        return false;
} */

void EventManager::mySleep()
{
    this->_w = true;
    std::thread thread = std::thread([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        this->_w = false;
    });
    thread.detach();
}


bool EventManager::IsKeyDownGame(irr::EKEY_CODE keyCode) const
{
    if (KeyIsDown[keyCode]) {
        return true;
    } else
        return false;
}

bool EventManager::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    if (KeyIsDown[keyCode]) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        return true;
    } else
        return false;
}

void EventManager::resetKeyIsPressed(void)
{
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsPressed[i] = false;
}

bool EventManager::getWait() const
{
    return this->_w;
}