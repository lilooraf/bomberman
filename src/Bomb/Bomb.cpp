/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "IPlayer.hpp"
#include "Bomb.hpp"
#include "Particles.hpp"

Bomb::Bomb(Map *map, Core *core, IPlayer *player)
{
    this->_player = player;
    this->_map = map;
    this->_core = core;
    this->_range = 2;
    this->_bombNum = 1;
    this->_bombMax = 1;
    this->_reload = true;
    this->_bombReloadTime = 4;
    reloadBombs();
    this->_smgr = this->_map->getSceneManager();
    this->_mesh_tnt = this->_smgr->getMesh("./assets/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/tnt.obj");
    this->_blocksBroken = 0;
    this->_itemsGot = 0;
    this->_dropChancePercent = 50;
}

Bomb::~Bomb()
{
    this->_reload = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
}

void Bomb::explodesLeft(int x, int y, std::vector<IPlayer *> allPlayers)
{
    int random = 0;
    this->_allPlayers = this->_core->getGame()->getPlayers();
    bool isDestroyed = false;

    for (int i = x; i < x + this->_range + 1; i++) {
        if (isDestroyed == true)
            break;
        if ((i % 2 == 0 && y % 2 == 0) || i > this->_map->getMapX() - 2)
            break;
        addParticles();
        this->_particles.back()->initParticles(i, y);
        int id = 0;
        for (IPlayer *player : allPlayers) {
            if (player == nullptr)
                continue;
            if (i == player->getMapPos().first && y == player->getMapPos().second) {
                if (i == this->_player->getMapPos().first && y == this->_player->getMapPos().second && this->_player->isIA());
                else
                    player->killPlayer(id);
            }
            id++;
        }
        if ((isDestroyed = this->_map->deleteBlockAtPos(i, y)) == true) {
            this->_blocksBroken++;
            random = rand() % 100;
            if (random < this->_dropChancePercent)
                this->_map->addChest(i, y);
        }
    }
}

void Bomb::explodesRight(int x, int y, std::vector<IPlayer *> allPlayers)
{
    int random = 0;
    this->_allPlayers = this->_core->getGame()->getPlayers();
    bool isDestroyed = false;

    for (int i = x; i > x - (this->_range + 1); i--) {
        if (isDestroyed == true)
            break;
        if ((i % 2 == 0 && y % 2 == 0) || i < 1)
            break;
        addParticles();
        this->_particles.back()->initParticles(i, y);
        int id = 0;
        for (IPlayer *player : allPlayers) {
            if (player == nullptr)
                continue;
            if (i == player->getMapPos().first && y == player->getMapPos().second) {
                if (i == this->_player->getMapPos().first && y == this->_player->getMapPos().second && this->_player->isIA());
                else
                    player->killPlayer(id);
            }
            id++;
        }
        if ((isDestroyed = this->_map->deleteBlockAtPos(i, y)) == true) {
            this->_blocksBroken++;
            random = rand() % 100;
            if (random < this->_dropChancePercent)
                this->_map->addChest(i, y);
        }
    }
}

void Bomb::explodesDown(int x, int y, std::vector<IPlayer *> allPlayers)
{
    int random = 0;
    this->_allPlayers = this->_core->getGame()->getPlayers();
    bool isDestroyed = false;

    for (int j = y; j < y + this->_range + 1; j++) {
        if (isDestroyed == true)
            break;
        if ((j % 2 == 0 && x % 2 == 0) || j > this->_map->getMapY() - 2)
            break;
        addParticles();
        this->_particles.back()->initParticles(x, j);
        int id = 0;
        for (IPlayer *player : allPlayers) {
            if (player == nullptr)
                continue;
            if (x == player->getMapPos().first && j == player->getMapPos().second) {
                if (x == this->_player->getMapPos().first && j == this->_player->getMapPos().second && this->_player->isIA());
                else
                    player->killPlayer(id);
            }
            id++;
        }
        if ((isDestroyed = this->_map->deleteBlockAtPos(x, j)) == true) {
            this->_blocksBroken++;
            random = rand() % 100;
            if (random < this->_dropChancePercent)
                this->_map->addChest(x, j);
        }
    }
}

void Bomb::explodesUp(int x, int y, std::vector<IPlayer *> allPlayers)
{
    int random = 0;
    this->_allPlayers = this->_core->getGame()->getPlayers();
    bool isDestroyed = false;

    for (int j = y; j > y - (this->_range + 1); j--) {
        if (isDestroyed == true)
            break;
        if ((j % 2 == 0 && x % 2 == 0) || j < 1)
            break;
        addParticles();
        this->_particles.back()->initParticles(x, j);
        int id = 0;
        for (IPlayer *player : allPlayers) {
            if (player == nullptr)
                continue;
            if (x == player->getMapPos().first && j == player->getMapPos().second) {
                if (x == this->_player->getMapPos().first && j == this->_player->getMapPos().second && this->_player->isIA());
                else
                    player->killPlayer(id);
            }
            id++;
        }
        if ((isDestroyed = this->_map->deleteBlockAtPos(x, j)) == true) {
            this->_blocksBroken++;
            random = rand() % 100;
            if (random < this->_dropChancePercent)
                this->_map->addChest(x, j);
        }
    }
}

void Bomb::dropBomb(int x, int z)
{
    this->_core->getMusic()->loadSound("pose", 1);
    this->_node_tnt = this->_map->makeNode(this->_mesh_tnt, x - (this->_map->getMapX() / 2), 1, z - (this->_map->getMapY() / 2));
    this->_core->getMusic()->loadSound("pchit", 2);
    this->_waitingBombs.push_back(this->_node_tnt);
    std::thread thread = std::thread([&, x, z]() {
        bool isSet = false;
        for (int i = 1000; i; i--) {
            while (!this->_core->getGame()->isRunning());
            if (isSet == false)
                isSet = this->_core->getGame()->setPlayersTntCollision(this->_node_tnt, x, z);
            if (!this->_core->isGameRunning())
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
        this->_core->getMusic()->loadSound("boum", 1);
        this->_waitingBombs.at(0)->setPosition(irr::core::vector3df(INFINITY, INFINITY, INFINITY));
        this->_waitingBombs.erase(this->_waitingBombs.begin());
        this->explodesLeft(x, z, _allPlayers);
        this->explodesRight(x, z, _allPlayers);
        this->explodesDown(x, z, _allPlayers);
        this->explodesUp(x, z, _allPlayers);
        std::thread thread2 = std::thread([&]() {
            for (int i = 0; i < 1000 && this->_core->isGameRunning(); i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            for (Particles *particle : this->_particles)
                particle->stopFire();
        });
        thread2.detach();
    });
    thread.detach();
}

void Bomb::reloadBombs()
{
    std::thread thread = std::thread([&]() {
        while (this->_reload && this->_core->isGameRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (this->_bombNum < this->_bombMax) {
                for (int i = 1000; i && this->_reload && this->_core->isGameRunning(); i--)
                    std::this_thread::sleep_for(std::chrono::milliseconds(this->_bombReloadTime));
                this->_bombNum++;
            }
        }
    });
    thread.detach();
}

int Bomb::getBombNum() const
{
    return this->_bombNum;
}

void Bomb::setBombNum(int bombNum)
{
    this->_bombNum = bombNum;
}

void Bomb::setReload(bool reload)
{
    this->_reload = reload;
}

void Bomb::addParticles()
{
    this->_particles.push_back(new Particles(this->_core, this->_map));
}
void Bomb::setBombRange(int range)
{
    this->_range = range;
}

void Bomb::setCurrentBomb(int currentBomb)
{
    this->_bombNum = currentBomb;
}

void Bomb::setMaxBomb(int maxBomb)
{
    this->_bombMax = maxBomb;
}

void Bomb::setReloadTime(int reloadTime)
{
    this->_bombReloadTime = reloadTime;
}

bool Bomb::isGameExist() const
{
    return this->_gameExist;
}