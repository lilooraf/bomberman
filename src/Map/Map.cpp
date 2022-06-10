/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#include "Map.hpp"

Map::Map(Core *core, int scale, int x, int y)
{
    this->_core = core;
    srand(time(NULL));
    if (this->_core->getLoad() == false)
        randomiser(y, x, 0);
    x *= 2;
    y *= 2;
    if (x < 5)
        x = 5;
    if (y < 5)
        y = 5;
    if (x % 2 == 0)
        x++;
    if (y % 2 == 0)
        y++;
    this->_device = this->_core->getWindow()->getDevice();
    this->_var_scale = scale;
    this->_proportion_scale_block = this->_var_scale * 2;
    this->_const_x = 0;
    this->_const_z = 0;
    this->_scale = irr::core::vector3df(this->_var_scale, this->_var_scale, this->_var_scale);
    this->_smgr = this->_core->getWindow()->getSmgr();
    this->_mesh = this->_smgr->getMesh("./assets/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/Grass_Block.obj");
    this->_mesh_wall = this->_smgr->getMesh("./assets/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/wall.obj");
    this->_mesh_wall2 = this->_smgr->getMesh("./assets/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/wall2.obj");
    this->_mesh_block = this->_smgr->getMesh("./assets/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/block.obj");
    this->_mesh_chest = this->_smgr->getMesh("./assets/minecraft-grass-block/source/Minecraft_Grass_Block_OBJ/chest.obj");
    if (!this->_mesh || !this->_mesh_wall || !this->_mesh_wall2 || !this->_mesh_block)
        throw std::runtime_error("Map meshes cannot be loaded");
    this->_mapx = x;
    this->_mapy = y;
    MakeGround(x + 20, y + 4);
    MakeWall(x, y);
    makeExtention(x + 10, y + 4);
    (this->_core->getLoad() == false) ? MakeBlock(x, y) : loadMap(); 
    int  x_cam = ((x / 2) / 10);
    int  y_cam = ((y / 2) / 10);
    if (x_cam < 1)
        x_cam = 1;
    if (y_cam < 1)
        y_cam = 1;
    this->_smgr->addCameraSceneNode(0, irr::core::vector3df(0, 300 * x_cam, 100 * y_cam), irr::core::vector3df(0, 0, 0));
    /* this->_smgr->addCameraSceneNodeFPS();
    this->_smgr->getActiveCamera()->setPosition(irr::core::vector3df(0, 300 * x_cam, 100 * y_cam)); */
    this->_fireTexture = this->_core->getWindow()->getDriver()->getTexture("./assets/fire.png");
}

Map::~Map()
{
    for (std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *> node : this->_block)
        std::get<2>(node)->remove();
}

irr::scene::IAnimatedMeshSceneNode *Map::makeNode(irr::scene::IAnimatedMesh *mesh, int x, int y, int z)
{
    irr::scene::IAnimatedMeshSceneNode *node = this->_smgr->addAnimatedMeshSceneNode(mesh);

    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setScale(this->_scale);
    node->setPosition(irr::core::vector3df(this->_proportion_scale_block * x + this->_const_x, this->_proportion_scale_block * y, this->_proportion_scale_block * z + this->_const_z));
    const irr::core::aabbox3d<irr::f32> &hitbox = node->getTransformedBoundingBox();
    this->_radius = hitbox.MaxEdge * 7 - hitbox.getCenter();
    //node->setDebugDataVisible(1);
    this->_selector.push_back(this->_smgr->createOctreeTriangleSelector(node->getMesh(), node, 128));
    return node;
}

void Map::MakeGround(int width, int height)
{
    if ((width % 2) == 0 && (height % 2) == 0) {
        this->_const_x = _proportion_scale_block / 2;
        this->_const_z = _proportion_scale_block / 2;
    } else if ((width % 2) == 0) {
        this->_const_x = _proportion_scale_block / 2;
    } else if ((height % 2) == 0) {
        this->_const_z = _proportion_scale_block / 2;
    }
    for (int i = ((width / 2) * -1); ((width % 2) == 0) ? i < (width / 2) : i <= (width / 2); i++)
        for (int j = ((height / 2) * -1); ((height % 2) == 0) ? j < (height / 2) : j <= (height / 2) ; j++)
            makeNode(this->_mesh, i, 0, j);
}

void Map::MakeWall(int width, int height)
{
    int b = 1;

    for (int j = ((height / 2) * -1); ((height % 2) == 0) ? j < (height / 2) : j <= (height / 2) ; j++) {
        if (j == ((height / 2) * -1) || (((height % 2) == 0) ? j + 1 == (height / 2) : j == (height / 2)))
            for (int i = ((width / 2) * -1); ((width % 2) == 0) ? i < (width / 2) : i <= (width / 2); i++)
                this->_mapBlocks.push_back(makeNode(this->_mesh_wall, i, 1, j));
        else {
            if (b == 0) {
                for (int i = ((width / 2) * -1); ((width % 2) == 0) ? i < (width / 2) : i <= (width / 2); i+=2)
                    if (i == ((width / 2)) || i == ((width / 2) * -1))
                        this->_mapBlocks.push_back(makeNode(this->_mesh_wall, i, 1, j));
                    else
                        this->_mapBlocks.push_back(makeNode(this->_mesh_wall2, i, 1, j));
                b = 1;
            } else {
                this->_mapBlocks.push_back(makeNode(this->_mesh_wall, ((width / 2) * -1), 1, j));
                this->_mapBlocks.push_back(makeNode(this->_mesh_wall, (width / 2), 1, j));
                b = 0;
            }
        }
    }   
}

void Map::makeExtention(int width, int height)
{
     int b = 1;

    for (int j = ((height / 2) * -1); ((height % 2) == 0) ? j < (height / 2) : j <= (height / 2) ; j++) {
        if (j == ((height / 2) * -1) || (((height % 2) == 0) ? j + 1 == (height / 2) : j == (height / 2)))
            for (int i = ((width / 2) * -1); ((width % 2) == 0) ? i < (width / 2) : i <= (width / 2); i++)
                this->_mapBlocks.push_back(makeNode(this->_mesh_wall, i, 1, j));
        else {
            if (b == 0) {
                for (int i = ((width / 2) * -1); ((width % 2) == 0) ? i < (width / 2) : i <= (width / 2); i+=2)
                    if (i == ((width / 2)) || i == ((width / 2) * -1))
                        this->_mapBlocks.push_back(makeNode(this->_mesh_wall, i, 1, j));
                b = 1;
            } else {
                this->_mapBlocks.push_back(makeNode(this->_mesh_wall, ((width / 2) * -1), 1, j));
                this->_mapBlocks.push_back(makeNode(this->_mesh_wall, (width / 2), 1, j));
                b = 0;
            }
        }
    }
}

void Map::MakeBlock(int width, int height)
{
    int i = 0;

    for (std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *> coords : this->_block) {
        irr::scene::IAnimatedMeshSceneNode *node = makeNode(this->_mesh_block, std::get<0>(coords) - (width / 2), 1, std::get<1>(coords) - (height / 2));
        coords = std::make_tuple(std::get<0>(coords), std::get<1>(coords), node);
        this->_mapBlocks.push_back(node);
        this->_breakableBlocks.push_back(node);
        this->_block.erase(this->_block.begin() + i);
        this->_block.insert(this->_block.begin() + i, coords);
        i++;
    }
}

void Map::randomiser(int x, int y, float p)
{
    std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *> coords;
    int i = 1;
    int j = 1;

    x = 2 * x - 1;
    y = 2 * y - 1;
    while (j < y + 1) {
        while (i < x + 1) {
            if ((i == 1 && j == 1) || (i == 2 && j == 1) || (i == 1 && j == 2)
            || (i == 1 && j == y) || (i == 1 && j == y - 1) || (i == 2 && j == y)
            || (i == x && j == y) || (i == x - 1 && j == y) || (i == x && j == y - 1)
            || (i == x && j == 1) || (i == x - 1 && j == 1) || (i == x && j == 2));
            else if ((rand() % 100) + 1 <= p * 100) {
                coords = std::make_tuple(j, i, nullptr);
                this->_block.push_back(coords);
            }
            if (j % 2 == 0)
                i += 2;
            else
                i++;
        }
        i = 1;
        j++;
    }
}

bool Map::deleteBlockAtPos(int x, int z)
{
    int i = 0;

    for (std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *>coords : this->_block) {
        if (std::get<0>(coords) == x && std::get<1>(coords) == z) {
            irr::scene::IAnimatedMeshSceneNode *node = std::get<2>(coords);
            node->setPosition(irr::core::vector3df(INFINITY, INFINITY, INFINITY));
            this->_block.erase(this->_block.begin() + i);
            return true;
        }
        i++;
    }
    return false;
}

irr::scene::IAnimatedMeshSceneNode *Map::getBlockAtPos(int x, int z)
{
    for (std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *>coords : this->_block) {
        if (std::get<0>(coords) == x && std::get<1>(coords) == z) {
            return std::get<2>(coords);
        }
    }
    return nullptr;
}

void Map::draw()
{
    this->_smgr->drawAll();
}

std::vector<irr::scene::ITriangleSelector *> Map::getSelector() const
{
    return this->_selector;
}

void Map::setSelector(irr::scene::ITriangleSelector *selector, int at)
{
    this->_selector.at(at) = selector;
}

irr::core::vector3df Map::getRadius() const
{
    return this->_radius;
}

irr::scene::ISceneManager *Map::getSceneManager(void)
{
    return this->_smgr;
}

int Map::getMapX()
{
    return this->_mapx;
}

int Map::getMapY()
{
    return this->_mapy;
}


void Map::saveMap()
{
    std::ofstream myfile;
    myfile.open(SAVE_PATH);

    for (std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *> coords : this->_block)
        myfile << std::get<0>(coords) << " " << 1 << " " << std::get<1>(coords) << std::endl;
    myfile.close();
}

void Map::loadMap()
{
    std::ifstream inFile;
    std::string name;
    std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *> coords;
    int b = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    inFile.open(SAVE_PATH);
    while (getline(inFile, name)) {
        std::stringstream line(name);
        line >> j;
        line >> k;
        line >> i;
        if (this->_mapx - 2 < j || this->_mapy - 2 < i)
            throw std::runtime_error("Map cannot be loaded size is to big.");
        coords = std::make_tuple(j, i, nullptr);
        this->_block.push_back(coords);
        b = 0;
    }
    inFile.close();
    if (this->_block.empty() == true)
        throw std::runtime_error("Map cannot be loaded.");
    MakeBlock(this->getMapX(), this->getMapY());
}

irr::video::ITexture *Map::getFireTexture() const
{
    return this->_fireTexture;
}

std::vector<std::tuple<int, int, irr::scene::IAnimatedMeshSceneNode *>> Map::getBlocks() const
{
    return this->_block;
}

std::vector<irr::scene::IAnimatedMeshSceneNode *> Map::getMapBlocks() const
{
    return this->_mapBlocks;
}

std::vector<irr::scene::IAnimatedMeshSceneNode *> Map::getBreakableBlocks() const
{
    return this->_breakableBlocks;
}

irr::scene::IAnimatedMesh *Map::getMeshChest() const
{
    return this->_mesh_chest;
}

std::vector<irr::scene::IAnimatedMeshSceneNode *> Map::getChests() const
{
    return this->_chests;
}

void Map::addChest(int x, int z)
{
    this->_chests.push_back(makeNode(this->_mesh_chest, x - this->_core->getMapWidth(), 1, z - this->_core->getMapHeight()));
}

void Map::deleteChestInVect(int at)
{
    this->_chests.at(at)->setPosition(irr::core::vector3df(INFINITY, INFINITY, INFINITY));
    this->_chests.erase(this->_chests.begin() + at);
}

bool Map::checkChestAtPost(int x, int z)
{
    int i = 0;

    for (irr::scene::IAnimatedMeshSceneNode *chest : this->_chests) {
        if (chest == nullptr)
            continue;
        if ((int)((chest->getPosition().X + this->_core->getMapScale()) / (this->_core->getMapScale() * 2) + (getMapX() / 2)) == x && (int)((chest->getPosition().Z + this->_core->getMapScale()) / (this->_core->getMapScale() * 2) + (getMapY() / 2)) == z) {
            deleteChestInVect(i);
            return true;
        }
        i++;
    }
    return false;
}