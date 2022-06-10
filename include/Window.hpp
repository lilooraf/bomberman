/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Window
*/

#include "defs.hpp"

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "MainMenu.hpp"
#include "EventManager.hpp"

class Window {
    public:
        Window(int const &width = 1920, int const &height = 1080);
        ~Window();
        int getWidth() const;
        int getHeight() const;
        int getScale() const;
        irr::IrrlichtDevice *getDevice() const;
        irr::video::IVideoDriver *getDriver() const;
        irr::scene::ISceneManager *getSmgr() const;
        irr::gui::IGUIEnvironment *getGui() const;
        irr::gui::IGUIFont *getFont24() const;
        irr::gui::IGUIFont *getFont28() const;
        irr::gui::IGUIFont *getFont72() const;
        EventManager getReceiver() const;
        void run();
    protected:
	private:
        int _width;
        int _height;
        irr::gui::IGUIEnvironment *_gui;
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;
        EventManager _receiver;
        irr::gui::IGUIFont *_font24;
        irr::gui::IGUIFont *_font28;
        irr::gui::IGUIFont *_font72;
        // std::vector<irr::gui::IGUIFont *> *_font;
};

#endif /* !WINDOW_HPP_ */
