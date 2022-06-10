/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Particles
*/

#include "Particles.hpp"
#include "Core.hpp"
#include "Map.hpp"

Particles::Particles(Core *core, Map *map)
{
    this->_core = core;
    this->_map = map;
    this->_smgr = this->_core->getWindow()->getSmgr();
    this->_driver = this->_core->getWindow()->getDriver();
    this->_texture = this->_map->getFireTexture();
}

Particles::~Particles()
{
}

void Particles::initParticles(int x, int z)
{
    int goodX = (x - this->_map->getMapX() / 2) * this->_core->getMapScale() * 2;
    int goodY = this->_core->getMapScale() * 2;
    int goodZ = (z - this->_map->getMapY() / 2) * this->_core->getMapScale() * 2;

    this->_ps = this->_smgr->addParticleSystemSceneNode(false);
    this->_em = this->_ps->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7),
		irr::core::vector3df(0.0f,0.06f,0.0f),
        20,100,
		irr::video::SColor(0,200,80,25),
		irr::video::SColor(0,0,0,0),
		800,800,0,
		irr::core::dimension2df(10.f,10.f),
		irr::core::dimension2df(20.f,20.f));
    this->_ps->setEmitter(this->_em);
    this->_em->drop();
    this->_paf = this->_ps->createFadeOutParticleAffector();
    this->_ps->addAffector(this->_paf);
    this->_paf->drop();
    this->_ps->setPosition(irr::core::vector3df(goodX, goodY, goodZ));
	this->_ps->setScale(irr::core::vector3df(0.7, 0.7, 0.7));
	this->_ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	this->_ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	this->_ps->setMaterialTexture(0, this->_texture);
	this->_ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void Particles::stopFire()
{
    this->_em = this->_ps->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7),
		irr::core::vector3df(0.0f,0.06f,0.0f),
        20,100,
		irr::video::SColor(0,200,80,25),
		irr::video::SColor(0,0,0,0),
		0,0,0,
		irr::core::dimension2df(10.f,10.f),
		irr::core::dimension2df(20.f,20.f));
    this->_ps->setEmitter(this->_em);
    this->_em->drop();
}
