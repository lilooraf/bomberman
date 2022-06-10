/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** HowMenu
*/

#include "defs.hpp"

#ifndef HOWMENU_HPP_
#define HOWMENU_HPP_

#include "IMenu.hpp"
#include "EventManager.hpp"

class Core;

class HowMenu : public IMenu {
    public:
        HowMenu(Core *core);
        ~HowMenu();

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
        irr::video::ITexture *_back_ground;

        irr::gui::IGUIButton *_back_button_gui;
        irr::video::ITexture *_back_button_pre_tx;
        irr::video::ITexture *_back_button_post_tx;
        irr::video::ITexture *_back_button_hover_tx;
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>_current_button;
};

#endif /* !HOWMENU_HPP_ */
