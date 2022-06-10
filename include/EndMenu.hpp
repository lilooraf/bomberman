/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EndMenu
*/

#include "defs.hpp"

#ifndef ENDMENU_HPP_
#define ENDMENU_HPP_

#include "IMenu.hpp"

class Core;

class EndMenu : public IMenu {
    public:
        EndMenu(Core *core, int player_id);
        ~EndMenu();

        void run();
        void createButtons();
        void splashScreen();
        void stopMenu();
        void useMenuEvents();
        int buttonAction();
        void drawBackground();
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>checkNextButton(int x, int y);
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
        irr::video::ITexture *_again_button_pre_tx;
        irr::video::ITexture *_again_button_post_tx;
        irr::video::ITexture *_again_button_hover_tx;
        irr::gui::IGUIButton *_again_button_gui;
        irr::video::ITexture *_quit_button_pre_tx;
        irr::video::ITexture *_quit_button_post_tx;
        irr::video::ITexture *_quit_button_hover_tx;
        irr::gui::IGUIButton *_quit_button_gui;
        irr::video::ITexture *_main_button_pre_tx;
        irr::video::ITexture *_main_button_post_tx;
        irr::video::ITexture *_main_button_hover_tx;
        irr::gui::IGUIButton *_main_button_gui;
        irr::gui::IGUIStaticText *_text_end_game;
        int _player_id;
        irr::gui::IGUIFont *_font;
        irr::gui::IGUIStaticText *_title_text;
        std::vector<std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>>_button_array;
        std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>_current_button;
};

#endif /* !ENDMENU_HPP_ */
