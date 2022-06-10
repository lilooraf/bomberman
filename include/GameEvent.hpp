/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEvent
*/

#include "EventManager.hpp"

#ifndef GAMEEVENT_HPP_
#define GAMEEVENT_HPP_

class Game;

class GameEvent {
    public:
        GameEvent(Game *game);
        ~GameEvent();

        void run();
        void checkPlayer1Event();
        void checkPlayer2Event();
        void checkPlayer3Event();
        void checkPlayer4Event();
    protected:
    private:
        Game *_game;
        EventManager _receiver;
};

#endif /* !GAMEEVENT_HPP_ */
