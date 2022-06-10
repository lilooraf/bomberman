/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Core
*/

#include "defs.hpp"

#ifndef CORE_HPP_
#define CORE_HPP_

#include "Window.hpp"
#include "MainMenu.hpp"
#include "CharacterMenu.hpp"
#include "EscMenu.hpp"
#include "EndMenu.hpp"
#include "Music.hpp"
#include "HowMenu.hpp"
#include "CreditMenu.hpp"
#include "SettingsMenu.hpp"

class Game;

class Core {
    public:
        Core();
        ~Core();

        Window *getWindow() const;
        void runCharacterMenu();
        void runGame();
        void runEscMenu();
        void resumeGame();
        void runMainMenu();
        void runSplashScreen();
        void runEndMenu();
        void runHowMenu();
        void runCreditMenu();
        void runSettingsMenu();
        int getMapWidth() const;
        int getMapHeight() const;
        int getMapScale() const;
        void setMapWidth(int width);
        void setMapHeight(int height);
        void setEndMenu(bool b);
        void setEndPlayerId(int id);
        void setMapScale(int scale);
        bool getLoad() const;
        void setLoad(bool load);
        bool checkIfLoadable();
        void quitGame();
        void setGameRunning(bool);
        bool isGameRunning() const;
        Game *getGame() const;
        void setHowMenu(bool b);
        void setCreditMenu(bool b);
        void setSettingsMenu(bool b);
        void setBackToMainMenu(bool b);
        bool getBackToMainMenu() const;
        void setCharacterMenu(bool b);
        bool getCharacterMenu() const;
        void pushBackInPlayers(std::pair<int, playerTexture_t> player);
        Music *getMusic() const;
        void setAllKeyMap();
        std::vector<int> getKeyMap0() const;
        void setKeyMap0(int code, int at);
        std::vector<int> getKeyMap1() const;
        void setKeyMap1(int code, int at);
        std::vector<int> getKeyMap2() const;
        void setKeyMap2(int code, int at);
        std::vector<int> getKeyMap3() const;
        void setKeyMap3(int code, int at);
        std::vector<int> getKeyMap4() const;
        void setKeyMap4(int code, int at);
    protected:
    private:
        Window *_window;
        IMenu *_menu;
        Game *_game;
        Music *_music;
        int _mapScale;
        int _mapWidth;
        int _mapHeight;
        bool _load;
        bool _gameRunning;
        bool _backToMainMenu;
        bool _characterMenu;
        bool _endMenu;
        bool _howMenu;
        bool _creditMenu;
        bool _settingsMenu;
        int _endPlayerId;
        int _player1_tx;
        int _player2_tx;
        int _player3_tx;
        int _player4_tx;
        int _player1_input;
        int _player2_input;
        int _player3_input;
        int _player4_input;
        std::vector<std::pair<int, playerTexture_t>> _players;
        std::vector<int> _keyMap0;
        std::vector<int> _keyMap1;
        std::vector<int> _keyMap2;
        std::vector<int> _keyMap3;
        std::vector<int> _keyMap4;
};

#endif /* !CORE_HPP_ */
