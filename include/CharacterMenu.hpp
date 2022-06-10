/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterMenu
*/

#include "defs.hpp"

#ifndef CHARACTERMENU_HPP_
#define CHARACTERMENU_HPP_

#include "IMenu.hpp"

class Core;

typedef struct playerTexture
{
    int id;
    irr::video::ITexture *tex;
} playerTexture_t;

class CharacterMenu : public IMenu {
    public:
        CharacterMenu(Core *core);
        ~CharacterMenu();

        int buttonAction();
        int buttonActionPlayer1();
        int buttonActionPlayer2();
        int buttonActionPlayer3();
        int buttonActionPlayer4();
        void drawBackground();
        void splashScreen();
        void createButtons1();
        void createButtons2();
        void createButtons3();
        void run();
        void stopMenu();
        void useMenuEvents();
        void loadAllPlayerTextures();
        void initAllPlayers();
        std::string getTexturePath(std::string path);
        irr::video::ITexture *loadTexture(std::string path);
        void createImages();
        void setLittleImages();
        void setPrevImages();
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>checkNextButton(int x, int y);
    protected:
    private:
        Core *_core;
        int _stop;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        irr::gui::IGUIEnvironment *_gui;
        irr::video::ITexture *_back_ground_tx;
        irr::video::ITexture *_left_pre_tx;
        irr::video::ITexture *_left_post_tx;
        irr::video::ITexture *_left_hover_tx;
        irr::video::ITexture *_right_pre_tx;
        irr::video::ITexture *_right_post_tx;
        irr::video::ITexture *_right_hover_tx;
        irr::video::ITexture *_play_button_pre_tx;
        irr::video::ITexture *_play_button_post_tx;
        irr::video::ITexture *_play_button_hover_tx;
        irr::gui::IGUIButton *_play_button_gui;
        irr::video::ITexture *_back_button_pre_tx;
        irr::video::ITexture *_back_button_post_tx;
        irr::video::ITexture *_back_button_hover_tx;
        irr::gui::IGUIButton *_back_button_gui;
        irr::video::ITexture *_player_tx;
        irr::video::ITexture *_ia_tx;
        irr::video::ITexture *_nothing_tx;
        irr::gui::IGUIImage *_little_img1;
        irr::gui::IGUIImage *_little_img2;
        irr::gui::IGUIImage *_little_img3;
        irr::gui::IGUIImage *_little_img4;
        irr::gui::IGUIImage *_prev_img1;
        irr::gui::IGUIImage *_prev_img2;
        irr::gui::IGUIImage *_prev_img3;
        irr::gui::IGUIImage *_prev_img4;
        std::vector<std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>>_button_array;
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>_current_button;
        std::pair<int, playerTexture_t> _player1;
        std::pair<int, playerTexture_t> _player2;
        std::pair<int, playerTexture_t> _player3;
        std::pair<int, playerTexture_t> _player4;
        std::vector<playerTexture_t> _allPlayerTexture;

        irr::gui::IGUIButton *_right1_button_gui;
        irr::gui::IGUIButton *_right2_button_gui;
        irr::gui::IGUIButton *_right3_button_gui;
        irr::gui::IGUIButton *_right4_button_gui;
        irr::gui::IGUIButton *_right5_button_gui;
        irr::gui::IGUIButton *_right6_button_gui;
        irr::gui::IGUIButton *_right7_button_gui;
        irr::gui::IGUIButton *_right8_button_gui;
        irr::gui::IGUIButton *_left1_button_gui;
        irr::gui::IGUIButton *_left2_button_gui;
        irr::gui::IGUIButton *_left3_button_gui;
        irr::gui::IGUIButton *_left4_button_gui;
        irr::gui::IGUIButton *_left5_button_gui;
        irr::gui::IGUIButton *_left6_button_gui;
        irr::gui::IGUIButton *_left7_button_gui;
        irr::gui::IGUIButton *_left8_button_gui;

};

#endif /* !CHARACTERMENU_HPP_ */
