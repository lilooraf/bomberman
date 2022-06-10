/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Core
*/

#include "Game.hpp"
#include "Core.hpp"

Core::Core()
{
    this->_game = nullptr;
    this->_gameRunning = false;
    this->_backToMainMenu = false;
    this->_endMenu = false;
    this->_howMenu = false;
    this->_settingsMenu = false;
    this->_window = new Window();
    this->_mapWidth = 7;
    this->_mapHeight = 6;
    this->_mapScale = 12;
    setAllKeyMap();
    this->_menu = new MainMenu(this);
    this->_music = new Music();
    // this->_music->muteMusic();
}

Core::~Core()
{
    delete(this->_window);
}

void Core::setAllKeyMap()
{
    this->_keyMap0.push_back(irr::KEY_ESCAPE);
    this->_keyMap0.push_back(irr::KEY_RETURN);

    this->_keyMap1.push_back('Z');
    this->_keyMap1.push_back('Q');
    this->_keyMap1.push_back('S');
    this->_keyMap1.push_back('D');
    this->_keyMap1.push_back(' ');

    this->_keyMap2.push_back('I');
    this->_keyMap2.push_back('J');
    this->_keyMap2.push_back('K');
    this->_keyMap2.push_back('L');
    this->_keyMap2.push_back('M');

    this->_keyMap3.push_back(38);
    this->_keyMap3.push_back(37);
    this->_keyMap3.push_back(40);
    this->_keyMap3.push_back(39);
    this->_keyMap3.push_back(163);

    this->_keyMap4.push_back('T');
    this->_keyMap4.push_back('F');
    this->_keyMap4.push_back('G');
    this->_keyMap4.push_back('H');
    this->_keyMap4.push_back('Y');
}

Window *Core::getWindow() const
{
    return this->_window;
}

void Core::runCharacterMenu()
{
    this->_menu = new CharacterMenu(this);
    this->_menu->run(); 
    delete(this->_menu);
    if (this->_gameRunning) {
        this->_music->stopMusic();
        this->_music->loadSound("3_2_1_GO", 5);
        runGame();
    }
    else
        runMainMenu();
}

void Core::runMainMenu()
{
    this->_menu = new MainMenu(this);
    if (!this->_music->isMusicPlaying())
        this->_music->loadMusic("menu");
    this->_menu->run();
    delete(this->_menu);
    if (this->_characterMenu) {
        this->_characterMenu = false;
        runCharacterMenu();
    }
    if (this->_howMenu) {
        this->_howMenu = false;
        runHowMenu();
    }
    if (this->_settingsMenu) {
        this->_settingsMenu = false;
        runSettingsMenu();
    }
    if (this->_creditMenu) {
        this->_creditMenu = false;
        runCreditMenu();
    }
}

void Core::runGame()
{
    this->_game = new Game(this, this->_players);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    this->_game->run();
    this->_gameRunning = false;
    delete(this->_game);
    this->_music->stopMusic();
    this->_players.clear();
    if (this->_backToMainMenu) {
        this->_backToMainMenu = false;
        runMainMenu();
    }
    if (this->_endMenu) {
        this->_endMenu = false;
        runEndMenu();
    }
}

void Core::runEscMenu()
{
    this->_menu = new EscMenu(this, this->_game);
    this->_menu->run();
    delete(this->_menu);
}

void Core::runEndMenu()
{
    this->_menu = new EndMenu(this, this->_endPlayerId);
    this->_menu->run();
    delete(this->_menu);
    if (this->_backToMainMenu) {
        this->_backToMainMenu = false;
        runMainMenu();
    }
    if (this->_characterMenu) {
        this->_characterMenu = false;
        runCharacterMenu();
    }
}

void Core::runHowMenu()
{
    this->_menu = new HowMenu(this);
    this->_menu->run();
    delete(this->_menu);
    if (this->_backToMainMenu) {
        this->_backToMainMenu = false;
        runMainMenu();
    }
}

void Core::runCreditMenu()
{
    this->_menu = new CreditMenu(this);
    this->_menu->run();
    delete(this->_menu);
    if (this->_backToMainMenu) {
        this->_backToMainMenu = false;
        runMainMenu();
    }
}

void Core::runSettingsMenu()
{
    this->_menu = new SettingsMenu(this);
    this->_menu->run();
    delete(this->_menu);
    if (this->_backToMainMenu) {
        this->_backToMainMenu = false;
        runMainMenu();
    }
}

void Core::resumeGame()
{
    delete(this->_menu);
}

void Core::quitGame()
{
    delete(this->_game);
}

void Core::runSplashScreen()
{
    this->_menu->splashScreen();
}

void Core::setBackToMainMenu(bool b)
{
    this->_backToMainMenu = b;
}

bool Core::getBackToMainMenu() const
{
    return this->_backToMainMenu;
}

void Core::setHowMenu(bool b)
{
    this->_howMenu = b;
}

void Core::setCreditMenu(bool b)
{
    this->_creditMenu = b;
}

void Core::setSettingsMenu(bool b)
{
    this->_settingsMenu = b;
}

void Core::setCharacterMenu(bool b)
{
    this->_characterMenu = b;
}

void Core::setEndMenu(bool b)
{
    this->_endMenu = b;
}

void Core::setEndPlayerId(int id)
{
    this->_endPlayerId = id;
}

bool Core::getCharacterMenu() const
{
    return this->_characterMenu;
}

bool Core::isGameRunning() const
{
    return this->_gameRunning;
}

int Core::getMapWidth() const
{
    return this->_mapWidth;
}

int Core::getMapHeight() const
{
    return this->_mapHeight;
}

int Core::getMapScale() const
{
    return this->_mapScale;
}

void Core::setMapWidth(int width)
{
    this->_mapWidth = width;
}

void Core::setMapHeight(int height)
{
    this->_mapHeight = height;
}

void Core::setMapScale(int scale)
{
    this->_mapScale = scale;
}

bool Core::getLoad() const
{
    return this->_load;
}

void Core::setLoad(bool load)
{
    this->_load = load;
}

void Core::setGameRunning(bool b)
{
    this->_gameRunning = b;
}


bool Core::checkIfLoadable()
{
    std::fstream fs;
    fs.open(SAVE_PATH, std::fstream::in);

    if (!fs.is_open())
        return false;
    fs.close();
    return true;
}

Game *Core::getGame() const
{
    return this->_game;
}

void Core::pushBackInPlayers(std::pair<int, playerTexture_t> player)
{
    this->_players.push_back(player);
}

Music *Core::getMusic() const
{
    return this->_music;
}

std::vector<int> Core::getKeyMap0() const
{
    return this->_keyMap0;
}

void Core::setKeyMap0(int code, int at)
{
    this->_keyMap0.at(at) = code;
}

std::vector<int> Core::getKeyMap1() const
{
    return this->_keyMap1;
}

void Core::setKeyMap1(int code, int at)
{
    this->_keyMap1.at(at) = code;
}

std::vector<int> Core::getKeyMap2() const
{
    return this->_keyMap2;
}

void Core::setKeyMap2(int code, int at)
{
    this->_keyMap2.at(at) = code;
}


std::vector<int> Core::getKeyMap3() const
{
    return this->_keyMap3;
}

void Core::setKeyMap3(int code, int at)
{
    this->_keyMap3.at(at) = code;
}


std::vector<int> Core::getKeyMap4() const
{
    return this->_keyMap4;
}

void Core::setKeyMap4(int code, int at)
{
    this->_keyMap4.at(at) = code;
}
