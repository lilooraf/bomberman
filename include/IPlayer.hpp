/*
** EPITECH PROJECT, 2020
** tek2
** File description:
** IPlayer
*/

#include "defs.hpp"
#include "Core.hpp"
#include "Map.hpp"

#ifndef IPLAYER_HPP_
#define IPLAYER_HPP_

#include "EventManager.hpp"

class Bomb;

class IPlayer {
    public:
        virtual ~IPlayer() {};

        virtual irr::scene::IAnimatedMeshSceneNode *getPlayerNode() = 0;
        virtual irr::core::vector3df getPlayerPos() = 0;
        virtual void up() = 0;
        virtual void down() = 0;
        virtual void right() = 0;
        virtual void left() = 0;
        virtual void drop() = 0;
        virtual void stop() = 0;
        virtual void setDeltaTime() = 0;
        virtual std::pair<int, int> getMapPos() const = 0;
        virtual void killPlayer(int id) = 0;
        virtual bool isAlive() const = 0;
        virtual void setMs(int) = 0;
        virtual int getMs() const = 0;
        virtual Bomb *getBomb() const = 0;
        virtual int getKill() const = 0;
        virtual int getDestroyedBlock() const = 0;
        virtual void setKill(int) = 0;
        virtual void setDestroyedBlock(int) = 0;
        virtual void brainIA() = 0;
        virtual bool isIA() const = 0;
        virtual void resetThen() = 0;
        virtual void resetNow() = 0;
    protected:
    private:
};

#endif /* !IPLAYER_HPP_ */
