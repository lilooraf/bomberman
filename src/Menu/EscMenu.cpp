/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EscMenu
*/

#include "Game.hpp"
#include "Core.hpp"
#include "EscMenu.hpp"

EscMenu::EscMenu(Core *core, Game *game)
{
    this->_core = core;
    this->_game = game;
    this->_stop = DEFAULT;
    this->_device = this->_core->getWindow()->getDevice();
    this->_driver = this->_core->getWindow()->getDriver();
    this->_smgr = this->_core->getWindow()->getSmgr();
    this->_gui = this->_core->getWindow()->getGui();
    this->_core->getMusic()->pauseMusic(true);
    this->_core->getGame()->setRunning(false);
    this->_receiver = this->_core->getWindow()->getReceiver();
    this->_core->getWindow()->getDevice()->getCursorControl()->setVisible(true);
    this->_back_ground = this->_driver->getTexture("./assets/BACK.png");
    this->_resume_button_gui = nullptr;
    this->_resume_button_pre_tx = this->_driver->getTexture("./assets/RESUME_PRE.png");
    this->_resume_button_post_tx = this->_driver->getTexture("./assets/RESUME_POST.png");
    this->_resume_button_hover_tx = this->_driver->getTexture("./assets/RESUME_HOVER.png");
    this->_save_button_gui = nullptr;
    this->_save_button_pre_tx = this->_driver->getTexture("./assets/SAVE_PRE.png");
    this->_save_button_post_tx = this->_driver->getTexture("./assets/SAVE_POST.png");
    this->_save_button_hover_tx = this->_driver->getTexture("./assets/SAVE_HOVER.png");
    this->_option_button_gui = nullptr;
    this->_option_button_pre_tx = this->_driver->getTexture("./assets/OPTION_PRE.png");
    this->_option_button_post_tx = this->_driver->getTexture("./assets/OPTION_POST.png");
    this->_option_button_hover_tx = this->_driver->getTexture("./assets/OPTION_HOVER.png");
    this->_main_button_gui = nullptr;
    this->_main_button_pre_tx = this->_driver->getTexture("./assets/MAIN_MENU_PRE.png");
    this->_main_button_post_tx = this->_driver->getTexture("./assets/MAIN_MENU_POST.png");
    this->_main_button_hover_tx = this->_driver->getTexture("./assets/MAIN_MENU_HOVER.png");
}

EscMenu::~EscMenu()
{
    this->_core->getMusic()->pauseMusic(false);
    this->_core->getGame()->setRunning(true);
    this->_core->getWindow()->getDevice()->getCursorControl()->setVisible(false);
    this->_main_button_gui->remove();
    this->_option_button_gui->remove();
    this->_save_button_gui->remove();
    this->_resume_button_gui->remove();
}

void EscMenu::createButtons()
{
    this->_resume_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(1900 / 3, 1080 / 3, 1900 / 1.5, 1080 / 2.6));
    this->_resume_button_gui->setImage(this->_resume_button_pre_tx);
    this->_resume_button_gui->setPressedImage(this->_resume_button_post_tx);
    this->_resume_button_gui->setScaleImage();
    this->_resume_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 0, this->_resume_button_gui, this->_resume_button_pre_tx, this->_resume_button_hover_tx));
    this->_current_button = std::make_tuple(0, 0, this->_resume_button_gui, this->_resume_button_pre_tx, this->_resume_button_hover_tx);
    this->_save_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(1900 / 3, 1080 / 3 + 80, 1900 / 1.5, 1080 / 2.6 + 80));
    this->_save_button_gui->setImage(this->_save_button_pre_tx);
    this->_save_button_gui->setPressedImage(this->_save_button_post_tx);
    this->_save_button_gui->setScaleImage();
    this->_save_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 0, this->_save_button_gui, this->_save_button_pre_tx, this->_save_button_hover_tx));
    this->_option_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(1900 / 3, 1080 / 3 + 160, 1900 / 2.1, 1080 / 2.6 + 160));
    this->_option_button_gui->setImage(this->_option_button_pre_tx);
    this->_option_button_gui->setPressedImage(this->_option_button_post_tx);
    this->_option_button_gui->setScaleImage();
    this->_option_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(2, 0, this->_option_button_gui, this->_option_button_pre_tx, this->_option_button_hover_tx));
    this->_main_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(1900 / 3 + 361, 1080 / 3 + 160, 1900 / 2.1 + 361, 1080 / 2.6 + 160));
    this->_main_button_gui->setImage(this->_main_button_pre_tx);
    this->_main_button_gui->setPressedImage(this->_main_button_post_tx);
    this->_main_button_gui->setScaleImage();
    this->_main_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(2, 1, this->_main_button_gui, this->_main_button_pre_tx, this->_main_button_hover_tx));
}

std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>EscMenu::checkNextButton(int x, int y)
{
    for (std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *> button : this->_button_array) {
        if (std::get<0>(button) == x && std::get<1>(button) == y)
            if (!std::get<2>(button)->isEnabled()) {
                return checkNextButton(x + (x - std::get<0>(this->_current_button)), y + (y - std::get<1>(this->_current_button)));
            } else
                return button;
    }
    for (int i = y; i >= 0; i--) {
        for (std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *> button : this->_button_array) {
            if (std::get<0>(button) == x && std::get<1>(button) == i)
                if (!std::get<2>(button)->isEnabled()) {
                    return checkNextButton(x + (x - std::get<0>(this->_current_button)), y + (y - std::get<1>(this->_current_button)));
                } else
                    return button;
    }
    }
    return this->_current_button;
}

void EscMenu::useMenuEvents()
{
    std::get<2>(this->_current_button)->setImage(std::get<3>(this->_current_button));
    if (this->_core->getWindow()->getReceiver().IsKeyDown((irr::EKEY_CODE)this->_core->getKeyMap1().at(0)))
        this->_current_button = checkNextButton(std::get<0>(this->_current_button) - 1, std::get<1>(this->_current_button));
    if (this->_core->getWindow()->getReceiver().IsKeyDown((irr::EKEY_CODE)this->_core->getKeyMap1().at(1)))
        this->_current_button = checkNextButton(std::get<0>(this->_current_button), std::get<1>(this->_current_button) - 1);
    if (this->_core->getWindow()->getReceiver().IsKeyDown((irr::EKEY_CODE)this->_core->getKeyMap1().at(2)))
        this->_current_button = checkNextButton(std::get<0>(this->_current_button) + 1, std::get<1>(this->_current_button));
    if (this->_core->getWindow()->getReceiver().IsKeyDown((irr::EKEY_CODE)this->_core->getKeyMap1().at(3)))
        this->_current_button = checkNextButton(std::get<0>(this->_current_button), std::get<1>(this->_current_button) + 1);
    if (this->_core->getWindow()->getReceiver().IsKeyDown((irr::EKEY_CODE)this->_core->getKeyMap0().at(1)) && std::get<2>(this->_current_button)->isEnabled())
        std::get<2>(this->_current_button)->setPressed(true);
    std::get<2>(this->_current_button)->setImage(std::get<4>(this->_current_button));
    if (this->_core->getWindow()->getReceiver().IsKeyDown((irr::EKEY_CODE)this->_core->getKeyMap0().at(0)))
        this->_resume_button_gui->setPressed(true);
}

int EscMenu::buttonAction()
{
    if (this->_resume_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_resume_button_gui->setPressed(false);
        return NEXT;
    }
    if (this->_save_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_game->getMap()->saveMap();
        this->_save_button_gui->setPressed(false);
    }
    if (this->_option_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_option_button_gui->setPressed(false);
        return _ERROR;
    }
    if (this->_main_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_main_button_gui->setPressed(false);
        this->_core->setBackToMainMenu(true);
        return EXIT;
    }
    return DEFAULT;
}

void EscMenu::drawBackground()
{
    //this->_driver->draw2DImage(this->_back_ground, irr::core::rect<irr::s32>(0, 0, this->_core->getWindow()->getWidth(), this->_core->getWindow()->getHeight()), irr::core::rect<irr::s32>(0, 0, BG_WIDTH, BG_HEIGHT));
}

void EscMenu::run()
{
    createButtons();
    while (this->_device->run() && this->_stop != EXIT && this->_stop != NEXT) {
        this->_driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        drawBackground();
        useMenuEvents();
        this->_stop = buttonAction();
        this->_smgr->drawAll();
        this->_gui->drawAll();
        this->_driver->endScene();
    }
}

void EscMenu::splashScreen()
{
}

void EscMenu::stopMenu()
{
    
}