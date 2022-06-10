/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#include "defs.hpp"

#ifndef MAP_HPP_
#define MAP_HPP_

#include "Core.hpp"

class Map {
    public:
        Map(Core *core, int scale, int x, int y);
        ~Map();
        irr::scene::IAnimatedMeshSceneNode *makeNode(irr::scene::IAnimatedMesh *mesh, int x, int y, int z);
        void randomiser(int x, int y, float p);
        void draw();
        void MakeGround(int width, int height);
        void MakeWall(int width, int height);
        void MakeBlock(int width, int height);
        void makeMap(int x, int y);
        void makeExtention(int width, int height);
        bool deleteBlockAtPos(int x, int z);
        irr::scene::IAnimatedMeshSceneNode *getBlockAtPos(int x, int z);
        std::vector<irr::scene::ITriangleSelector *>getSelector() const;
        void setSelector(irr::scene::ITriangleSelector *selector, int at);
        irr::core::vector3df getRadius() const;
        irr::scene::ISceneManager *getSceneManager();
        int getMapX();
        int getMapY();
        void saveMap();
        void loadMap();
        irr::video::ITexture *getFireTexture() const;
        std::vector<std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *>> getBlocks() const;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> getMapBlocks() const;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> getBreakableBlocks() const;
        irr::scene::IAnimatedMesh *getMeshChest() const;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> getChests() const;
        void addChest(int x, int z);
        void deleteChestInVect(int at);
        bool checkChestAtPost(int x, int z);
    protected:
    private:
        Core *_core;
        irr::IrrlichtDevice *_device;
        irr::scene::ISceneManager *_smgr;
        irr::scene::IAnimatedMesh *_mesh;
        irr::scene::IAnimatedMesh *_mesh_wall;
        irr::scene::IAnimatedMesh *_mesh_wall2;
        irr::scene::IAnimatedMesh *_mesh_block;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> _mapBlocks;
        irr::scene::IAnimatedMesh *_mesh_chest;
        std::vector<std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *>> _block;
        irr::core::vector3df _scale;
        int _var_scale;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> _breakableBlocks;
        int _proportion_scale_block;
        float _const_x;
        float _const_z;
        std::vector<irr::scene::ITriangleSelector *>_selector;
        irr::core::vector3df _radius;
        int _mapx;
        int _mapy;
        irr::video::ITexture *_fireTexture;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> _chests;
};

#endif /* !MAP_HPP_ */
