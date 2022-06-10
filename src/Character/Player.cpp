/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#include "Bomb.hpp"
#include "Player.hpp"

Player::Player(Core *core, Map *map, float x, float z, float r, irr::video::ITexture *tex)
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
        throw std::runtime_error("Player cannot be loaded");
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
}

Player::~Player()
{
    delete(this->_bomb);
}

void Player::setDeltaTime()
{
    this->_now = this->_core->getWindow()->getDevice()->getTimer()->getTime();
    this->_frameDeltaTime = (irr::f32)(this->_now - this->_then) / 1000.f;
    this->_then = this->_now;
}

void Player::up()
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

void Player::down()
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

void Player::right()
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

void Player::left()
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

void Player::drop()
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

std::pair<int, int> Player::getMapPos() const
{
    return std::make_pair((this->_anms->getPosition().X + this->_core->getMapScale()) / (this->_core->getMapScale() * 2) + (this->_map->getMapX() / 2), (this->_anms->getPosition().Z  + this->_core->getMapScale()) / (this->_core->getMapScale() * 2) + (this->_map->getMapY() / 2));
}

void Player::stop()
{
    this->_anms->setFrameLoop(45, 45);
    this->_moving = false;
}

irr::scene::IAnimatedMeshSceneNode *Player::getPlayerNode()
{
    return this->_anms;
}

irr::core::vector3df Player::getPlayerPos()
{
    return this->_anms->getPosition();
}

void Player::killPlayer(int id)
{
    this->_core->getMusic()->loadSound("death", 1);
    std::cout << "Steve " << id << " fucking exploded." << std::endl;
    this->_anms->setPosition(irr::core::vector3df(INFINITY, INFINITY, INFINITY));
    this->_alive = false;
    this->_bomb->setReload(false);
}

bool Player::isAlive() const
{
    return this->_alive;
}

void Player::setMs(int speed)
{
    this->_ms = speed;
}

int Player::getMs() const
{
    return this->_ms;
}

Bomb *Player::getBomb() const
{
    return this->_bomb;
}

int Player::getKill() const
{
    return this->_kill;
}

int Player::getDestroyedBlock() const
{
    return this->_destroyedBlock;
}

void Player::setKill(int kill)
{
    this->_kill = kill;
}

void Player::setDestroyedBlock(int destroyedBlock)
{
    this->_destroyedBlock = destroyedBlock;
}

bool Player::isIA() const
{
    return false;
}

void Player::resetThen()
{
    this->_then = this->_device->getTimer()->getTime();
}

void Player::resetNow()
{
    this->_now = this->_device->getTimer()->getTime();
}
