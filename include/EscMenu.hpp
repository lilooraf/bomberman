/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EscMenu
*/

#include "defs.hpp"

#ifndef ESCMENU_HPP_
#define ESCMENU_HPP_

#include "Map.hpp"
#include "IMenu.hpp"

class Core;
class Game;

class EscMenu : public IMenu {
    public:
        EscMenu(Core *core, Game *game);
        ~EscMenu();

        void run();
        void splashScreen();
        void createButtons();
        void stopMenu();
        void drawBackground();
        void useMenuEvents();
        int buttonAction();
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>checkNextButton(int x, int y);
    protected:
    private:
        Core *_core;
        Game *_game;
        int _stop;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        irr::gui::IGUIEnvironment *_gui;
        EventManager _receiver;
        irr::video::ITexture *_back_ground;
        irr::video::ITexture *_resume_button_pre_tx;
        irr::video::ITexture *_resume_button_post_tx;
        irr::video::ITexture *_resume_button_hover_tx;
        irr::gui::IGUIButton *_resume_button_gui;

        irr::video::ITexture *_save_button_pre_tx;
        irr::video::ITexture *_save_button_post_tx;
        irr::video::ITexture *_save_button_hover_tx;
        irr::gui::IGUIButton *_save_button_gui;

        irr::video::ITexture *_option_button_pre_tx;
        irr::video::ITexture *_option_button_post_tx;
        irr::video::ITexture *_option_button_hover_tx;
        irr::gui::IGUIButton *_option_button_gui;

        irr::video::ITexture *_main_button_pre_tx;
        irr::video::ITexture *_main_button_post_tx;
        irr::video::ITexture *_main_button_hover_tx;
        irr::gui::IGUIButton *_main_button_gui;

        std::vector<std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>>_button_array;
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>_current_button;
};

#endif /* !ESCMENU_HPP_ */
