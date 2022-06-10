/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EventManager
*/

#include "defs.hpp"
#include "MainMenu.hpp"

#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_

class EventManager : public irr::IEventReceiver {
    public:
        EventManager();
        ~EventManager();

        bool OnEvent(const irr::SEvent &event);
        bool IsKeyDownGame(irr::EKEY_CODE const keyCode) const;
        bool IsKeyDown(irr::EKEY_CODE const keyCode) const;
        bool IsKeyPressed(irr::EKEY_CODE const keyCode) const;
        void resetKeyIsPressed(void);
        void mySleep();
        bool getWait() const;
    protected:
    private:
        bool _w;
        std::vector<bool> KeyIsDown;
        std::vector<bool> KeyIsPressed;
};

#endif /* !EVENTMANAGER_HPP_ */
