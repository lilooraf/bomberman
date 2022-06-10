/*
** EPITECH PROJECT, 2020
** testirrlicht
** File description:
** playerIA
*/

#include "IPlayer.hpp"

#ifndef PLAYERIA_HPP_
#define PLAYERIA_HPP_


class PlayerIA : public IPlayer
{
    public:
        PlayerIA(Core *core, Map *map, float x, float z, float r, irr::video::ITexture *tex);
        ~PlayerIA();
        typedef enum {
            UP,
            DOWN,
            RIGHT,
            LEFT,
        } e_move;

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
        void brainIA();
        bool isIA() const;
        void resetThen();
        void resetNow();
    protected:
        bool isInRange(irr::f32);
        bool canGoAtPos(irr::f32, irr::f32, std::vector<irr::scene::IAnimatedMeshSceneNode *> list);
        void choseDirection(int, std::vector<irr::scene::IAnimatedMeshSceneNode *> list);
        bool directionIsReachable(int, std::vector<irr::scene::IAnimatedMeshSceneNode *> list);
        void dropBombIfPossible();
        bool playerInRange();
    private:
        Core *_core;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        irr::scene::IAnimatedMesh *_playerIA;
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
        int _direction;
        int _taken;
        int _rd;
};

#endif /* !PLAYERIA_HPP_ */
