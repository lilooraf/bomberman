/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameEvent
*/

#include "Game.hpp"
#include "GameEvent.hpp"

GameEvent::GameEvent(Game *game)
{
    this->_game = game;
    this->_receiver = this->_game->getCore()->getWindow()->getReceiver();
}

GameEvent::~GameEvent()
{
}

void GameEvent::checkPlayer1Event()
{
    if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap1().at(0)))
        this->_game->getPlayers()[0]->up();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap1().at(1)))
        this->_game->getPlayers()[0]->left();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap1().at(2)))
        this->_game->getPlayers()[0]->down();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap1().at(3)))
        this->_game->getPlayers()[0]->right();
    else
        this->_game->getPlayers()[0]->stop();
    if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap1().at(4)))
        this->_game->getPlayers()[0]->drop();
}

void GameEvent::checkPlayer2Event()
{
    if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap2().at(0)))
        this->_game->getPlayers()[1]->up();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap2().at(1)))
        this->_game->getPlayers()[1]->left();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap2().at(2)))
        this->_game->getPlayers()[1]->down();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap2().at(3)))
        this->_game->getPlayers()[1]->right();
    else
        this->_game->getPlayers()[1]->stop();
    if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap2().at(4)))
        this->_game->getPlayers()[1]->drop();
}

void GameEvent::checkPlayer3Event()
{
    if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap3().at(0)))
        this->_game->getPlayers()[2]->up();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap3().at(1)))
        this->_game->getPlayers()[2]->left();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap3().at(2)))
        this->_game->getPlayers()[2]->down();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap3().at(3)))
        this->_game->getPlayers()[2]->right();
    else
        this->_game->getPlayers()[2]->stop();
    if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap3().at(4)))
        this->_game->getPlayers()[2]->drop();
}

void GameEvent::checkPlayer4Event()
{
    if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap4().at(0)))
        this->_game->getPlayers()[3]->up();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap4().at(1)))
        this->_game->getPlayers()[3]->left();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap4().at(2)))
        this->_game->getPlayers()[3]->down();
    else if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap4().at(3)))
        this->_game->getPlayers()[3]->right();
    else
        this->_game->getPlayers()[3]->stop();
    if (this->_game->getCore()->getWindow()->getReceiver().IsKeyDownGame((irr::EKEY_CODE)this->_game->getCore()->getKeyMap4().at(4)))
        this->_game->getPlayers()[3]->drop();
}

void GameEvent::run()
{
    if (!this->_game->isRunning())
        return;

    //std::cout << this->_game->getPlayers().at(0)->isIA() << " " << this->_game->getPlayers().at(1)->isIA() << " " << this->_game->getPlayers().at(2)->isIA() << " " << this->_game->getPlayers().at(3)->isIA() << " " << std::endl;


    if (this->_game->getPlayers().at(0) != nullptr) {
        if (!this->_game->getPlayers().at(0)->isIA())
            checkPlayer1Event();
        if (this->_game->getPlayers().at(0)->isIA())
            this->_game->getPlayers().at(0)->brainIA();
    }
    if (this->_game->getPlayers().at(1) != nullptr) {
        if (!this->_game->getPlayers().at(1)->isIA())
            checkPlayer2Event();
        if (this->_game->getPlayers().at(1)->isIA())
            this->_game->getPlayers().at(1)->brainIA();
    }
    if (this->_game->getPlayers().at(2) != nullptr) {
        if (!this->_game->getPlayers().at(2)->isIA())
            checkPlayer3Event();
        if (this->_game->getPlayers().at(2)->isIA()) {
            this->_game->getPlayers().at(2)->brainIA();
        }
    }
    if (this->_game->getPlayers().at(3) != nullptr) {
        if (!this->_game->getPlayers().at(3)->isIA())
            checkPlayer4Event();
        if (this->_game->getPlayers().at(3)->isIA())
            this->_game->getPlayers().at(3)->brainIA();
    }
}