/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PlayerIA
*/

#include "Bomb.hpp"
#include "PlayerIA.hpp"

PlayerIA::PlayerIA(Core *core, Map *map, float x, float z, float r, irr::video::ITexture *tex)
{
    this->_core = core;
    this->_map = map;
    this->_moving = false;
    this->_alive = true;
    this->_then = 0;
    this->_now = 0;
    this->_ms = 100;
    this->_stop = false;
    this->_device = this->_core->getWindow()->getDevice();
    this->_driver = this->_core->getWindow()->getDriver();
    this->_smgr = this->_core->getWindow()->getSmgr();
    irr::u32 then = this->_device->getTimer()->getTime();
    this->_anms = this->_smgr->addAnimatedMeshSceneNode(this->_smgr->getMesh("./assets/media/m_s.b3d"), 0, -1, irr::core::vector3df(x, 12 * 2 * 2, z), irr::core::vector3df(0, r, 0));
    if (!this->_anms)
        throw std::runtime_error("PlayerIA cannot be loaded");
    this->_anms->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_anms->setFrameLoop(0, 0);
    this->_anms->setAnimationSpeed(this->_ms / 2);
    this->_anms->setScale(irr::core::vector3df(5.f, 5.f, 5.f));
    this->_anms->setMaterialTexture(0, tex);
    for (irr::scene::ITriangleSelector *selector : this->_map->getSelector()) {
        irr::scene::ISceneNodeAnimator *anim = this->_smgr->createCollisionResponseAnimator(selector, this->_anms, this->_map->getRadius(), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
        irr::scene::ISceneNodeAnimator *anim2 = this->_smgr->createCollisionResponseAnimator(selector, this->_smgr->getActiveCamera(), this->_map->getRadius(), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
        this->_anms->addAnimator(anim);
        this->_smgr->getActiveCamera()->addAnimator(anim2);
    }
    this->_bomb = new Bomb(this->_map, this->_core, this);
    this->_anms->addShadowVolumeSceneNode();
    this->_direction = UP;
    this->_taken = false;
    this->_rd;
}

PlayerIA::~PlayerIA()
{
    delete(this->_bomb);
}

void PlayerIA::setDeltaTime()
{
    this->_now = this->_core->getWindow()->getDevice()->getTimer()->getTime();
    this->_frameDeltaTime = (irr::f32)(this->_now - this->_then) / 1000.f;
    this->_then = this->_now;
}

void PlayerIA::up()
{
    if (!this->_alive)
        return;
    irr::core::vector3df pos = this->_anms->getPosition();

    pos.Z -= this->_ms * this->_frameDeltaTime;
    this->_anms->setRotation(irr::core::vector3df(0, 0, 0));
    if (!this->_moving) {
        this->_anms->setFrameLoop(1, 40);
        this->_moving = true;
    }
    this->_anms->setPosition(pos);
}

void PlayerIA::down()
{
    if (!this->_alive)
        return;
    irr::core::vector3df pos = this->_anms->getPosition();

    pos.Z += this->_ms * this->_frameDeltaTime;
    this->_anms->setRotation(irr::core::vector3df(0, 180, 0));
    if (!this->_moving) {
        this->_anms->setFrameLoop(1, 40);
        this->_moving = true;
    }
    this->_anms->setPosition(pos);
}

void PlayerIA::right()
{
    if (!this->_alive)
        return;
    irr::core::vector3df pos = this->_anms->getPosition();

    pos.X -= this->_ms * this->_frameDeltaTime;
    this->_anms->setRotation(irr::core::vector3df(0, 90, 0));
    if (!this->_moving) {
        this->_anms->setFrameLoop(1, 40);
        this->_moving = true;
    }
    this->_anms->setPosition(pos);
}

void PlayerIA::left()
{
    if (!this->_alive)
        return;
    irr::core::vector3df pos = this->_anms->getPosition();

    pos.X += this->_ms * this->_frameDeltaTime;
    this->_anms->setRotation(irr::core::vector3df(0, -90, 0));
    if (!this->_moving) {
        this->_anms->setFrameLoop(1, 40);
        this->_moving = true;
    }
    this->_anms->setPosition(pos);
}

void PlayerIA::drop()
{
    if (!this->_alive)
        return;
    if (this->_bomb->getBombNum() > 0 && this->_stop == false) {
        std::thread thread = std::thread([&]() {
            this->_stop = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            this->_stop = false;
        });
        thread.detach();
        this->_bomb->dropBomb(getMapPos().first, getMapPos().second);
        this->_bomb->setBombNum(this->_bomb->getBombNum() - 1);
    }
}

std::pair<int, int> PlayerIA::getMapPos() const
{
    return std::make_pair((this->_anms->getPosition().X + this->_core->getMapScale()) / (this->_core->getMapScale() * 2) + (this->_map->getMapX() / 2), (this->_anms->getPosition().Z  + this->_core->getMapScale()) / (this->_core->getMapScale() * 2) + ( this->_map->getMapY() / 2));
}

void PlayerIA::stop()
{
    this->_anms->setFrameLoop(45, 45);
    this->_moving = false;
}

irr::scene::IAnimatedMeshSceneNode *PlayerIA::getPlayerNode()
{
    return this->_anms;
}

irr::core::vector3df PlayerIA::getPlayerPos()
{
    return this->_anms->getPosition();
}

void PlayerIA::killPlayer(int id)
{
    std::cout << "Steve " << id << " fucking exploded." << std::endl;
    this->_anms->setPosition(irr::core::vector3df(INFINITY, INFINITY, INFINITY));
    this->_alive = false;
    this->_bomb->setReload(false);
}

bool PlayerIA::isAlive() const
{
    return this->_alive;
}

void PlayerIA::setMs(int speed)
{
    this->_ms = speed;
}

int PlayerIA::getMs() const
{
    return this->_ms;
}

Bomb *PlayerIA::getBomb() const
{
    return this->_bomb;
}

int PlayerIA::getKill() const
{
    return this->_kill;
}

int PlayerIA::getDestroyedBlock() const
{
    return this->_destroyedBlock;
}

void PlayerIA::setKill(int kill)
{
    this->_kill = kill;
}

void PlayerIA::setDestroyedBlock(int destroyedBlock)
{
    this->_destroyedBlock = destroyedBlock;
}

bool PlayerIA::isIA() const
{
    return true;
}

bool PlayerIA::canGoAtPos(irr::f32 x, irr::f32 y, std::vector<irr::scene::IAnimatedMeshSceneNode *> list)
{
    for (irr::scene::IAnimatedMeshSceneNode *node : list) {
        irr::core::vector3df block = node->getPosition();
        if ((x < (block.X + (irr::f32)this->_core->getMapScale()) && x > (block.X - (irr::f32)this->_core->getMapScale())) && (y < (block.Z + (irr::f32)this->_core->getMapScale()) && y > (block.Z - (irr::f32)this->_core->getMapScale())))
            return false;
    }
    return true;
}

void PlayerIA::resetThen()
{
    this->_then = this->_device->getTimer()->getTime();
}

void PlayerIA::resetNow()
{
    this->_now = this->_device->getTimer()->getTime();
}


bool PlayerIA::isInRange(irr::f32 i)
{
    int size = this->_core->getMapScale() / 2;

    for (int j = -size; j <= size; j++)
        if (((int)i + j) % (size * 2) == 0)
            return true;
    return false;
}

void PlayerIA::choseDirection(int rd, std::vector<irr::scene::IAnimatedMeshSceneNode *> list)
{
    int rad = (rand() % 6);

    if (directionIsReachable(this->_direction, list))
        this->_direction = (rad == 0) ? rd : this->_direction;
    else
        this->_direction = rd;
}

bool PlayerIA::directionIsReachable(int direction, std::vector<irr::scene::IAnimatedMeshSceneNode *> list)
{
    int range = this->_core->getMapScale() * 0.5;
    bool b = false;

    if (direction == UP && canGoAtPos(this->_anms->getPosition().X, this->_anms->getPosition().Z - ((irr::f32)this->_core->getMapScale() + range), list))
        b = true;
    if (direction == DOWN && canGoAtPos(this->_anms->getPosition().X, this->_anms->getPosition().Z + ((irr::f32)this->_core->getMapScale() + range), list))
        b = true;
    if (direction == RIGHT && canGoAtPos(this->_anms->getPosition().X - ((irr::f32)this->_core->getMapScale() + range), this->_anms->getPosition().Z, list))
        b = true;
    if (direction == LEFT && canGoAtPos(this->_anms->getPosition().X + ((irr::f32)this->_core->getMapScale() + range), this->_anms->getPosition().Z, list))
        b = true;
    return b;
}

bool PlayerIA::playerInRange()
{
    irr::core::vector3df pos;

    for (IPlayer *player : this->_core->getGame()->getPlayers()) {
        if (player == nullptr)
            continue;
        pos = player->getPlayerPos();
        if ((pos.X == this->getPlayerPos().X && pos.Z == this->getPlayerPos().Z))
            continue;
        if ((pos.X < (this->getPlayerPos().X + (irr::f32)this->_core->getMapScale() * 3) && pos.X > (this->getPlayerPos().X - (irr::f32)this->_core->getMapScale() * 3)) && (pos.Z < (this->getPlayerPos().Z + (irr::f32)this->_core->getMapScale() * 3) && pos.Z > (this->getPlayerPos().Z - (irr::f32)this->_core->getMapScale() * 3)))
            return true;
    }
    return false;
}

void PlayerIA::dropBombIfPossible()
{
    for (int i = 0; i <= 3; i++)
        if (!directionIsReachable(i, this->_map->getBreakableBlocks())/*  || playerInRange() */)
            drop();
}

void PlayerIA::brainIA()
{
    dropBombIfPossible();
    std::vector<irr::scene::IAnimatedMeshSceneNode *> list = this->_map->getMapBlocks();
    if (this->_rd >= 4 || this->_taken)
        this->_rd = rand() % 4;

    if (!this->_taken) {
        if (this->_rd == UP && !directionIsReachable(UP, list)) {
            this->_rd++;
            return brainIA();
        } else if (this->_rd == UP) {
            choseDirection(UP, list);
            this->_taken = true;
        }
        if (this->_rd == DOWN && !directionIsReachable(DOWN, list)) {
            this->_rd++;
            return brainIA();
        } else if (this->_rd == DOWN) {
            choseDirection(DOWN, list);
            this->_taken = true;
        }
        if (this->_rd == RIGHT && !directionIsReachable(RIGHT, list)) {
            this->_rd++;
            return brainIA();
        } else if (this->_rd == RIGHT){
            choseDirection(RIGHT, list);
            this->_taken = true;
        }
        if (this->_rd == LEFT && !directionIsReachable(LEFT, list)) {
            this->_rd++;
            return brainIA();
        } else if (this->_rd == LEFT) {
            choseDirection(LEFT, list);
            this->_taken = true;
        }
        if (!directionIsReachable(this->_direction, list) && directionIsReachable(this->_rd, list)) {
            choseDirection(this->_rd, list);
            this->_taken = true;
        }
        if (this->_taken) {
            std::thread thread = std::thread([&]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                this->_taken = false;
            });
            thread.detach();
        }
    }
    if (this->_direction == UP)
        this->up();
    if (this->_direction == DOWN)
        this->down();
    if (this->_direction == RIGHT)
        this->right();
    if (this->_direction == LEFT)
        this->left();
}