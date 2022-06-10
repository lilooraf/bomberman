/*
** EPITECH PROJECT, 2020
** testirrlicht
** File description:
** player
*/

#include "IPlayer.hpp"

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class Player : public IPlayer
{
    public:
        Player(Core *core, Map *map, float x, float z, float r, irr::video::ITexture *tex);
        ~Player();

        irr::scene::IAnimatedMeshSceneNode *getPlayerNode();
        irr::core::vector3df getPlayerPos();
        void up();
        void down();
        void right();
        void left();
        void drop();
        void stop();
        void setDeltaTime();
        std::pair<int, int> getMapPos() const;
        void killPlayer(int id);
        bool isAlive() const;
        void setMs(int);
        int getMs() const;
        Bomb *getBomb() const;
        int getKill() const;
        int getDestroyedBlock() const;
        void setKill(int);
        void setDestroyedBlock(int);
        void brainIA() {};
        bool isIA() const;
        void resetThen();
        void resetNow();
    protected:
    private:
        Core *_core;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        irr::scene::IAnimatedMesh *_player;
        irr::scene::IAnimatedMeshSceneNode *_anms;
        irr::u32 _then;
        irr::u32 _now;
        irr::f32 _frameDeltaTime;
        irr::f32 _ms;
        Map *_map;
        Bomb *_bomb;
        bool _stop;
        bool _moving;
        bool _alive;
        int _kill;
        int _destroyedBlock;
        bool _isIA;
};

#endif /* !PLAYER_HPP_ */
