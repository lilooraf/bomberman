/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenu
*/

#include "defs.hpp"

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "IMenu.hpp"
#include "EventManager.hpp"

class Core;

class MainMenu : public IMenu {
    public:
        MainMenu(Core *core);
        ~MainMenu();

        int buttonAction();
        void drawBackground();
        void run();
        void splashScreen();
        void createButtons();
        void useMenuEvents();
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>checkNextButton(int x, int y);
        void stopMenu();
    protected:
    private:
        Core *_core;
        int _stop;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        irr::gui::IGUIEnvironment *_gui;
        EventManager _receiver;
        irr::video::ITexture *_splash_tx;
        irr::video::ITexture *_back_ground;

        irr::gui::IGUIButton *_new_button_gui;
        irr::video::ITexture *_new_button_pre_tx;
        irr::video::ITexture *_new_button_post_tx;
        irr::video::ITexture *_new_button_hover_tx;
        irr::gui::IGUIButton *_load_button_gui;
        irr::video::ITexture *_load_button_pre_tx;
        irr::video::ITexture *_load_button_post_tx;
        irr::video::ITexture *_load_button_hover_tx;
        irr::gui::IGUIButton *_option_button_gui;
        irr::video::ITexture *_option_button_pre_tx;
        irr::video::ITexture *_option_button_post_tx;
        irr::video::ITexture *_option_button_hover_tx;
        irr::gui::IGUIButton *_quit_button_gui;
        irr::video::ITexture *_quit_button_pre_tx;
        irr::video::ITexture *_quit_button_post_tx;
        irr::video::ITexture *_quit_button_hover_tx;
        irr::gui::IGUIButton *_how_button_gui;
        irr::video::ITexture *_how_button_pre_tx;
        irr::video::ITexture *_how_button_post_tx;
        irr::video::ITexture *_how_button_hover_tx;
        irr::gui::IGUIButton *_credit_button_gui;
        irr::video::ITexture *_credit_button_pre_tx;
        irr::video::ITexture *_credit_button_post_tx;
        irr::video::ITexture *_credit_button_hover_tx;
        irr::video::ITexture *_over;
        irr::video::ITexture *_disabled_tx;
        std::vector<std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>>_button_array;
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>_current_button;
};

#endif /* !MAINMENU_HPP_ */
