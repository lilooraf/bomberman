/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Window
*/

#include "../../include/Window.hpp"

Window::Window(int const &width, int const &height)
{
    this->_width = width;
    this->_height = height;
    this->_receiver = EventManager();
    if ((this->_device = irr::createDevice(irr::video::EDT_OPENGL,
            irr::core::dimension2d<irr::u32>(this->_width, this->_height),
            32, false, true, false, &this->_receiver)) == NULL)
        throw std::runtime_error("Device cannot be loaded");
    this->_device->setWindowCaption(L"Bomberman");
    this->_device->getCursorControl()->setVisible(true);
    this->_driver = this->_device->getVideoDriver();
    this->_gui = this->_device->getGUIEnvironment();
    this->_smgr = this->_device->getSceneManager();
    this->_font24 = this->_device->getGUIEnvironment()->getFont("./assets/font/font24.bmp");
    this->_font28 = this->_device->getGUIEnvironment()->getFont("./assets/font/font28.bmp");
    this->_font72 = this->_device->getGUIEnvironment()->getFont("./assets/font/font72.bmp");
}

Window::~Window()
{
    this->_device->drop();
}


irr::IrrlichtDevice *Window::getDevice() const
{
    return this->_device;
}

irr::video::IVideoDriver *Window::getDriver() const
{
    return this->_driver;
}

irr::scene::ISceneManager *Window::getSmgr() const
{
    return this->_smgr;
}

irr::gui::IGUIEnvironment *Window::getGui() const
{
    return this->_gui;
}


irr::gui::IGUIFont *Window::getFont24() const
{
    return this->_font24;
}

irr::gui::IGUIFont *Window::getFont28() const
{
    return this->_font28;
}

irr::gui::IGUIFont *Window::getFont72() const
{
    return this->_font72;
}

int Window::getWidth() const
{
    return this->_driver->getScreenSize().Width;
}

int Window::getHeight() const
{
    return this->_driver->getScreenSize().Height;
}

EventManager Window::getReceiver() const
{
    return this->_receiver;
}

void Window::run()
{
}