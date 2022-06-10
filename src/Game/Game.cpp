/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#include "Core.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "PlayerIA.hpp"

Game::Game(Core *core, std::vector<std::pair<int, playerTexture_t>> players)
{
    this->_map = nullptr;
    this->_core = core;
    this->_core->setGameRunning(true);
    this->_device = this->_core->getWindow()->getDevice();
    this->_driver = this->_core->getWindow()->getDriver();
    this->_smgr = this->_core->getWindow()->getSmgr();
    this->_gui = this->_core->getWindow()->getGui();
    this->_receiver = this->_core->getWindow()->getReceiver();
    this->_core->getWindow()->getDevice()->getCursorControl()->setVisible(false);
    this->_inGame = false;
    this->_countDown = 3;
    this->_playerEvents = new GameEvent(this);
    this->_map = new Map(this->_core, this->_core->getMapScale(), this->_core->getMapWidth(), this->_core->getMapHeight());
    this->_running = true;
    this->_players = players;
    std::string path;
    path.assign(BASE_PATH).append(std::to_string(players.at(0).second.id)).append("pathTex.png");
    if (players.at(0).first == IA)
        this->_allPlayers.push_back(new PlayerIA(this->_core, this->_map, this->_core->getMapScale() * 2 * 5.85, this->_core->getMapScale() * 2 * -4.85, 135, this->_driver->getTexture(path.c_str())));
    else if (players.at(0).first != NOTHING)
        this->_allPlayers.push_back(new Player(this->_core, this->_map, this->_core->getMapScale() * 2 * 5.85, this->_core->getMapScale() * 2 * -4.85, 135, this->_driver->getTexture(path.c_str())));
    else
        this->_allPlayers.push_back(nullptr);
    path.assign(BASE_PATH).append(std::to_string(players.at(1).second.id)).append("pathTex.png");
    if (players.at(1).first == IA)
        this->_allPlayers.push_back(new PlayerIA(this->_core, this->_map, this->_core->getMapScale() * 2 * -5.85, this->_core->getMapScale() * 2 * 4.85, 315, this->_driver->getTexture(path.c_str())));
    else if (players.at(1).first != NOTHING)
        this->_allPlayers.push_back(new Player(this->_core, this->_map, this->_core->getMapScale() * 2 * -5.85, this->_core->getMapScale() * 2 * 4.85, 315, this->_driver->getTexture(path.c_str())));
    else
        this->_allPlayers.push_back(nullptr);
    path.assign(BASE_PATH).append(std::to_string(players.at(2).second.id)).append("pathTex.png");
    if (players.at(2).first == IA)
        this->_allPlayers.push_back(new PlayerIA(this->_core, this->_map, this->_core->getMapScale() * 2 * 5.85, this->_core->getMapScale() * 2 * 4.85, 45, this->_driver->getTexture(path.c_str())));
    else if (players.at(2).first != NOTHING)
        this->_allPlayers.push_back(new Player(this->_core, this->_map, this->_core->getMapScale() * 2 * 5.85, this->_core->getMapScale() * 2 * 4.85, 45, this->_driver->getTexture(path.c_str())));
    else
        this->_allPlayers.push_back(nullptr);
    path.assign(BASE_PATH).append(std::to_string(players.at(3).second.id)).append("pathTex.png");
    if (players.at(3).first == IA)
        this->_allPlayers.push_back(new PlayerIA(this->_core, this->_map, this->_core->getMapScale() * 2 * -5.85, this->_core->getMapScale() * 2 * -4.85, 225, this->_driver->getTexture(path.c_str())));
    else if (players.at(3).first != NOTHING)
        this->_allPlayers.push_back(new Player(this->_core, this->_map, this->_core->getMapScale() * 2 * -5.85, this->_core->getMapScale() * 2 * -4.85, 225, this->_driver->getTexture(path.c_str())));
    else
        this->_allPlayers.push_back(nullptr);
    for (int i = 0; i <= 3; i++) {
        if (i == 0)
            this->_countDownTextures.push_back(this->_driver->getTexture("./assets/GO.png"));
        else {
            std::string path;
            this->_countDownTextures.push_back(this->_driver->getTexture(path.assign("./assets/").append(std::to_string(i)).append(".png").c_str()));
        }
    }
    this->_hudTex = this->_driver->getTexture("./assets/HUD.png");
    this->_suddenDeathTex = this->_driver->getTexture("./assets/SDEATH.png");
    this->_suddenDeath = false;
    this->_time = new Time();
    this->_time->setDevice(this->_device);
    this->_time->setCore(this->_core);
    this->_point = this->_driver->getTexture("./assets/point.png");
    
}

Game::~Game()
{
    this->_core->setGameRunning(false);
    for (; !this->_allPlayers.empty(); ) {
        delete(*this->_allPlayers.begin());
        this->_allPlayers.erase(this->_allPlayers.begin());
    }
    this->_allPlayers.clear();
    delete(this->_map);
    this->_time->stopAll();
    delete(this->_time);
    this->_smgr->clear();
    this->_gui->clear();
    this->_receiver.resetKeyIsPressed();
    this->_core->getWindow()->getDevice()->getCursorControl()->setVisible(true);
}

void Game::setAllPlayersDaltaTime()
{
    for (IPlayer *player : this->_allPlayers) {
        if (player == nullptr)
            continue;
        player->setDeltaTime();
    }
}

int Game::checkEndGame()
{
    int i = 0;
    int alive = 0;
    int winner_id = 0;
    for (IPlayer *player : this->_allPlayers) {
        if (player == nullptr)
            continue;
        if (player->isAlive()) {
            this->_winner = player;
            winner_id = i;
            alive++;
        }
        i++;
    }
    if (alive == 1 || alive == 0) {
        endGame(winner_id);
        return EXIT;
    } else {
        if (this->_map->getBlocks().empty() && !this->_suddenDeath)
            suddenDeath();
    }
    return DEFAULT;
}

void Game::suddenDeath()
{
    this->_suddenDeath = true;
    for (IPlayer *player : this->_allPlayers) {
        if (player == nullptr)
            continue;
        player->setMs(player->getMs() * 2);
        player->getPlayerNode()->setAnimationSpeed(player->getMs() / 2);
        player->getBomb()->setCurrentBomb(10);
        player->getBomb()->setMaxBomb(15);
        player->getBomb()->setReloadTime(1);
        player->getBomb()->setBombRange(4);
    }
    this->_suddenDeathImage->setVisible(true);
    std::thread thread = std::thread([&]() {
        for (int i = 0; i < 1000 && this->_core->isGameRunning(); i++)
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        this->_suddenDeathImage->setVisible(false);
    });
    thread.detach();
}

void Game::endGame(int id)
{
    this->_core->setEndPlayerId(id);
    this->_core->setEndMenu(true);
}

void Game::createImages()
{
    this->_countDownImage = this->_gui->addImage(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 2 - 150, this->_core->getWindow()->getHeight() / 2 - 150, this->_core->getWindow()->getWidth() / 2 + 150, this->_core->getWindow()->getHeight() / 2 + 150));
    this->_suddenDeathImage = this->_gui->addImage(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 2 - 600, this->_core->getWindow()->getHeight() / 2 - 150, this->_core->getWindow()->getWidth() / 2 + 600, this->_core->getWindow()->getHeight() / 2 + 150));
    this->_suddenDeathImage->setImage(this->_suddenDeathTex);
    this->_suddenDeathImage->setScaleImage(true);
    this->_suddenDeathImage->setVisible(false);
    this->_hudImage = this->_gui->addImage(irr::core::rect<irr::s32>(0, 0, BG_WIDTH, BG_HEIGHT));
    this->_hudImage->setImage(this->_hudTex);
    this->_hudImage->setScaleImage(true);
    this->_p1Image = this->_gui->addImage(irr::core::rect<irr::s32>(125, 90, 200, 230));
    this->_p1Image->setImage(this->_players.at(0).second.tex);
    this->_p1Image->setScaleImage(true);
    this->_p2Image = this->_gui->addImage(irr::core::rect<irr::s32>(1715, 650, 1790, 810));
    this->_p2Image->setImage(this->_players.at(1).second.tex);
    this->_p2Image->setScaleImage(true);
    this->_p3Image = this->_gui->addImage(irr::core::rect<irr::s32>(125, 650, 200, 810));
    this->_p3Image->setImage(this->_players.at(2).second.tex);
    this->_p3Image->setScaleImage(true);
    this->_p4Image = this->_gui->addImage(irr::core::rect<irr::s32>(1715, 90, 1790, 230));
    this->_p4Image->setImage(this->_players.at(3).second.tex);
    this->_p4Image->setScaleImage(true);
    initPoint();
}

void Game::initPoint()
{
    for (size_t i = 0; i < 16; i++) {
        this->_imgPoint.push_back(this->_gui->addImage(irr::core::rect<irr::s32>(0, 0, 23, 23)));
        this->_imgPoint.at(i)->setImage(this->_point);
        this->_imgPoint.at(i)->setScaleImage(true);
    }
    // P1
    this->_imgPoint.at(0)->setRelativePosition(irr::core::position2d<irr::s32>(154 + 28 * 0, 244));
    this->_imgPoint.at(1)->setRelativePosition(irr::core::position2d<irr::s32>(154 + 28 * 1, 244));
    this->_imgPoint.at(2)->setRelativePosition(irr::core::position2d<irr::s32>(154 + 28 * 2, 244));
    this->_imgPoint.at(3)->setRelativePosition(irr::core::position2d<irr::s32>(154 + 28 * 3, 244));

    // P3
    this->_imgPoint.at(4)->setRelativePosition(irr::core::position2d<irr::s32>(154 + 28 * 0, 829));
    this->_imgPoint.at(5)->setRelativePosition(irr::core::position2d<irr::s32>(154 + 28 * 1, 829));
    this->_imgPoint.at(6)->setRelativePosition(irr::core::position2d<irr::s32>(154 + 28 * 2, 829));
    this->_imgPoint.at(7)->setRelativePosition(irr::core::position2d<irr::s32>(154 + 28 * 3, 829));

    // P2
    this->_imgPoint.at(8)->setRelativePosition(irr::core::position2d<irr::s32>(1658 + 28 * 0, 244));
    this->_imgPoint.at(9)->setRelativePosition(irr::core::position2d<irr::s32>(1658 + 28 * 1, 244));
    this->_imgPoint.at(10)->setRelativePosition(irr::core::position2d<irr::s32>(1658 + 28 * 2, 244));
    this->_imgPoint.at(11)->setRelativePosition(irr::core::position2d<irr::s32>(1658 + 28 * 3, 244));

    // P4
    this->_imgPoint.at(12)->setRelativePosition(irr::core::position2d<irr::s32>(1658 + 28 * 0, 829));
    this->_imgPoint.at(13)->setRelativePosition(irr::core::position2d<irr::s32>(1658 + 28 * 1, 829));
    this->_imgPoint.at(14)->setRelativePosition(irr::core::position2d<irr::s32>(1658 + 28 * 2, 829));
    this->_imgPoint.at(15)->setRelativePosition(irr::core::position2d<irr::s32>(1658 + 28 * 3, 829));
    
}

void Game::displayBonus(int id, char c)
{
    if (id == 1) {
        if (c == 'b')
            this->_imgPoint.at(0)->setVisible(false);
        if (c == 'g')
            this->_imgPoint.at(1)->setVisible(false);
        if (c == 'y')
            this->_imgPoint.at(2)->setVisible(false);
        if (c == 'r')
            this->_imgPoint.at(3)->setVisible(false);
    }
    if (id == 3) {
        if (c == 'b')
            this->_imgPoint.at(4)->setVisible(false);
        if (c == 'g')
            this->_imgPoint.at(5)->setVisible(false);
        if (c == 'y')
            this->_imgPoint.at(6)->setVisible(false);
        if (c == 'r')
            this->_imgPoint.at(7)->setVisible(false);
    }
    if (id == 4) {
        if (c == 'r')
            this->_imgPoint.at(8)->setVisible(false);
        if (c == 'y')
            this->_imgPoint.at(9)->setVisible(false);
        if (c == 'g')
            this->_imgPoint.at(10)->setVisible(false);
        if (c == 'b')
            this->_imgPoint.at(11)->setVisible(false);
    }
    if (id == 2) {
        if (c == 'r')
            this->_imgPoint.at(12)->setVisible(false);
        if (c == 'y')
            this->_imgPoint.at(13)->setVisible(false);
        if (c == 'g')
            this->_imgPoint.at(14)->setVisible(false);
        if (c == 'b')
            this->_imgPoint.at(15)->setVisible(false);
    }
}

void Game::hideBonus(int id, char c)
{
    if (id == 1) {
        if (c == 'b')
            this->_imgPoint.at(0)->setVisible(true);
        if (c == 'g')
            this->_imgPoint.at(1)->setVisible(true);
        if (c == 'y')
            this->_imgPoint.at(2)->setVisible(true);
        if (c == 'r')
            this->_imgPoint.at(3)->setVisible(true);
    }
    if (id == 3) {
        if (c == 'b')
            this->_imgPoint.at(4)->setVisible(true);
        if (c == 'g')
            this->_imgPoint.at(5)->setVisible(true);
        if (c == 'y')
            this->_imgPoint.at(6)->setVisible(true);
        if (c == 'r')
            this->_imgPoint.at(7)->setVisible(true);
    }
    if (id == 4) {
        if (c == 'r')
            this->_imgPoint.at(8)->setVisible(true);
        if (c == 'y')
            this->_imgPoint.at(9)->setVisible(true);
        if (c == 'g')
            this->_imgPoint.at(10)->setVisible(true);
        if (c == 'b')
            this->_imgPoint.at(11)->setVisible(true);
    }
    if (id == 2) {
        if (c == 'r')
            this->_imgPoint.at(12)->setVisible(true);
        if (c == 'y')
            this->_imgPoint.at(13)->setVisible(true);
        if (c == 'g')
            this->_imgPoint.at(14)->setVisible(true);
        if (c == 'b')
            this->_imgPoint.at(15)->setVisible(true);
    }
}

void Game::runPreGame()
{
    if (this->_countDown == 3 && this->_core->isGameRunning()) {
        this->_time->startTimeClock();
        this->_countDownImage->setImage(this->_countDownTextures.at(this->_countDown));
        this->_countDownImage->setScaleImage(true);
        this->_countDown = -1;
        std::thread thread = std::thread([&]() {
            for (int i = 0; i < 1000 && this->_core->isGameRunning(); i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->_countDown = 2;
        });
        thread.detach();
    }
    if (this->_countDown == 2 && this->_core->isGameRunning()) {
        this->_countDownImage->setImage(this->_countDownTextures.at(this->_countDown));
        this->_countDownImage->setScaleImage(true);
        this->_countDown = -1;
        std::thread thread = std::thread([&]() {
            for (int i = 0; i < 1000 && this->_core->isGameRunning(); i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->_countDown = 1;
        });
        thread.detach();
    }
    if (this->_countDown == 1 && this->_core->isGameRunning()) {
        this->_countDownImage->setImage(this->_countDownTextures.at(this->_countDown));
        this->_countDownImage->setScaleImage(true);
        this->_countDown = -1;
        std::thread thread = std::thread([&]() {
            for (int i = 0; i < 1000 && this->_core->isGameRunning(); i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->_countDown = 0;
        });
        thread.detach();
    }
    if (this->_countDown == 0 && this->_core->isGameRunning()) {
        this->_countDownImage->setImage(this->_countDownTextures.at(this->_countDown));
        this->_countDownImage->setScaleImage(true);
        this->_countDown = -1;
        std::thread thread = std::thread([&]() {
            this->_inGame = true;
            for (int i = 0; i < 1000 && this->_core->isGameRunning(); i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->_countDownImage->setVisible(false);
        });
        thread.detach();
        this->_time->startTime();
        this->_core->getMusic()->loadMusic("game");
        this->_countDown = -1;
    }
}

void Game::run()
{
    createImages();
    int stop = DEFAULT;
    while (this->_device->run() && stop != EXIT && !this->_core->getBackToMainMenu()) {
        if (this->_core->getWindow()->getReceiver().IsKeyDown((irr::EKEY_CODE)this->_core->getKeyMap0().at(0))) {
            this->_time->stopTime();
            this->_core->runEscMenu();
            for (IPlayer *player: this->_allPlayers)
                if (player != nullptr) {
                    player->resetNow();
                    player->resetThen();
                }
            this->_time->startTime();
        }
        this->_driver->beginScene(true, true, irr::video::SColor(0, 148, 193, 255));
        setAllPlayersDaltaTime();
        if (this->_inGame == true)
            this->_playerEvents->run();
        else
            runPreGame();
        // this->_playerEvents->run();
        allPlayersTakeChest();
        stop = checkEndGame();
        this->_smgr->drawAll();
        this->_gui->drawAll();
        this->_driver->endScene();
    }
}

Core *Game::getCore() const
{
    return this->_core;
}

std::vector<IPlayer *> Game::getPlayers() const
{
    return this->_allPlayers;
}

Map *Game::getMap() const
{
    return this->_map;
}

void Game::deletePlayerAt(int id)
{
    if (this->_allPlayers.size() < id)
        return;
    int i = 0;
    for (IPlayer *player : this->_allPlayers) {
        if (player == nullptr)
            continue;
        if (i == id) {
            delete(player);
            this->_allPlayers.erase(this->_allPlayers.begin() + id);
            break;
        }
        i++;
    }
}

bool Game::setPlayersTntCollision(irr::scene::IAnimatedMeshSceneNode *tnt, int x, int y)
{
    for (IPlayer *player : this->_allPlayers) {
        if (player == nullptr)
            continue;
        if ((player->getPlayerPos().X <= tnt->getPosition().X + (this->_core->getMapScale() * 2 - 2) && player->getPlayerPos().X >= tnt->getPosition().X - (this->_core->getMapScale() * 2 - 2)) && (player->getPlayerPos().Z <= tnt->getPosition().Z + (this->_core->getMapScale() * 2 - 2) && player->getPlayerPos().Z >= tnt->getPosition().Z - (this->_core->getMapScale() * 2 - 2)))
            return false;
    }
    for (IPlayer *player : this->_allPlayers) {
        if (player == nullptr)
            continue;
        irr::scene::ISceneNodeAnimator *anim = this->_smgr->createCollisionResponseAnimator(this->_smgr->createOctreeTriangleSelector(tnt->getMesh(), tnt), player->getPlayerNode(), this->_map->getRadius(), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
        player->getPlayerNode()->addAnimator(anim);
    }
    return true;
}

bool Game::isRunning() const
{
    return this->_running;
}

void Game::setRunning(bool state)
{
    this->_running = state;
}

void Game::allPlayersTakeChest()
{
    int id = 1;

    if (this->_map == nullptr || this->_map->getChests().empty())
        return;
    for (IPlayer *player : this->_allPlayers) {
        if (player != nullptr && (this->_map->checkChestAtPost(player->getMapPos().first, player->getMapPos().second)) == true)
            setPlayerBonus(player, id);
        id++;
    }
}

void Game::setPlayerBonus(IPlayer *player, int id)
{
    int random = rand() % 3;

    if (this->_suddenDeath == true)
        return;
    if (random == 0) {
        player->setMs(150);
        displayBonus(id, 'g');
        std::thread thread = std::thread([&, player, id]() {
            for (int i = 5000; i; i--) {
                while (!this->_core->getGame()->isRunning());
                if (!this->_core->isGameRunning())
                    return;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            if (player != nullptr && this->_suddenDeath == false) {
                player->setMs(100);
                hideBonus(id, 'g');
            }
        });
        thread.detach();
    }
    if (random == 1) {
        player->getBomb()->setBombRange(4);
        displayBonus(id, 'r');
        std::thread thread = std::thread([&, player, id]() {
            for (int i = 5000; i; i--) {
                while (!this->_core->getGame()->isRunning());
                if (!this->_core->isGameRunning())
                    return;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            if (player != nullptr && this->_suddenDeath == false) {
                player->getBomb()->setBombRange(2);
                hideBonus(id, 'r');
            }
        });
        thread.detach();
    }
    if (random == 2) {
        player->getBomb()->setReloadTime(2);
        displayBonus(id, 'y');
        std::thread thread = std::thread([&, player, id]() {
            for (int i = 5000; i; i--) {
                while (!this->_core->getGame()->isRunning());
                if (!this->_core->isGameRunning())
                    return;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            if (player != nullptr && this->_suddenDeath == false) {
                player->getBomb()->setReloadTime(4);
                hideBonus(id, 'y');
            }
        });
        thread.detach();
    }
}