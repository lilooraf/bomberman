/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "IPlayer.hpp"
#include "Bomb.hpp"
#include "Map.hpp"
#include "GameEvent.hpp"
#include "Time.hpp"

class Core;

class Game {
    public:
        Game(Core *core, std::vector<std::pair<int, playerTexture_t>> players);
        ~Game();

        void run();
        Core *getCore() const;
        std::vector<IPlayer *>getPlayers() const;
        Map *getMap() const;
        void setAllPlayersDaltaTime();
        void deletePlayerAt(int id);
        int checkEndGame();
        void endGame(int id);
        void suddenDeath();
        bool setPlayersTntCollision(irr::scene::IAnimatedMeshSceneNode *tnt, int x, int y);
        void runPreGame();
        void createImages();
        bool isRunning() const;
        void setRunning(bool);
        void allPlayersTakeChest();
        void initPoint();
        void displayBonus(int id, char c);
        void hideBonus(int id, char c);
    protected:
    private:
        Time *_time;
        Core *_core;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        irr::gui::IGUIEnvironment *_gui;
        EventManager _receiver;
        Map *_map;
        IPlayer *_player;
        Bomb *_bomb;
        std::vector<IPlayer *> _allPlayers;
        GameEvent *_playerEvents;
        IPlayer *_winner;
        bool _suddenDeath;
        bool _running;
        irr::gui::IGUIImage *_countDownImage;
        irr::gui::IGUIImage *_suddenDeathImage;
        irr::video::ITexture *_suddenDeathTex;
        irr::gui::IGUIImage *_hudImage;
        irr::video::ITexture *_hudTex;
        irr::gui::IGUIImage *_p1Image;
        irr::gui::IGUIImage *_p2Image;
        irr::gui::IGUIImage *_p3Image;
        irr::gui::IGUIImage *_p4Image;
        irr::video::ITexture *_point;
        // irr::gui::IGUIImage *_imgPoint;
        bool _inGame;
        int _countDown;
        std::vector<std::pair<int, playerTexture_t>> _players;
        std::vector<irr::video::ITexture *> _countDownTextures;
        std::vector<irr::gui::IGUIImage *> _imgPoint;
        void setPlayerBonus(IPlayer *player, int id);
};

#endif /* !GAME_HPP_ */
