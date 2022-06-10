/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "Game.hpp"
#include "Map.hpp"
#include "Core.hpp"

class IPlayer;
class Particles;

class Bomb {
    public:
        Bomb(Map *map, Core *core, IPlayer *player);
        ~Bomb();

        void explodesLeft(int x, int z, std::vector<IPlayer *> allPlayers);
        void explodesRight(int x, int z, std::vector<IPlayer *> allPlayers);
        void explodesDown(int x, int z, std::vector<IPlayer *> allPlayers);
        void explodesUp(int x, int z, std::vector<IPlayer *> allPlayers);
        void reloadBombs();
        int getBombNum() const;
        void setBombNum(int bombNum);
        void dropBomb(int x, int z);
        void setReload(bool reload);
        void addParticles();
        void setBombRange(int);
        void setCurrentBomb(int);
        void setMaxBomb(int);
        void setReloadTime(int);
        bool isGameExist() const;
    protected:
    private:
        Map *_map;
        Core *_core;
        IPlayer *_player;
        std::vector<Particles *> _particles;
        int _range;
        int _bombNum;
        int _bombReloadTime;
        bool _reload;
        int _bombMax;
        irr::scene::ISceneManager *_smgr;
        irr::scene::IAnimatedMesh *_mesh_tnt;
        irr::scene::IAnimatedMeshSceneNode *_node_tnt;
        std::vector<IPlayer *> _allPlayers;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> _waitingBombs;
        float _dropChancePercent;
        float _blocksBroken;
        float _itemsGot;
        bool _gameExist;
};

#endif /* !BOMB_HPP_ */
