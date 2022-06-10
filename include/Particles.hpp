/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Particles
*/

#include "Window.hpp"

#ifndef PARTICLES_HPP_
#define PARTICLES_HPP_

class Core;
class Map;

class Particles {
    public:
        Particles(Core *core, Map *map);
        ~Particles();

        void initParticles(int x, int y);
        void stopFire();
    protected:
    private:
        Core *_core;
        Map *_map;
        irr::scene::ISceneManager *_smgr;
        irr::video::IVideoDriver *_driver;
        irr::scene::IParticleSystemSceneNode *_ps;
        irr::scene::IParticleEmitter *_em;
        irr::scene::IParticleAffector *_paf;
        irr::video::ITexture *_texture;
};

#endif /* !PARTICLES_HPP_ */
