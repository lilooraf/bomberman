/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** HowMenu
*/

#include "Core.hpp"
#include "HowMenu.hpp"

HowMenu::HowMenu(Core *core)
{
    this->_core = core;
    this->_stop = DEFAULT;
    this->_device = this->_core->getWindow()->getDevice();
    this->_driver = this->_core->getWindow()->getDriver();
    this->_smgr = this->_core->getWindow()->getSmgr();
    this->_gui = this->_core->getWindow()->getGui();
    this->_receiver = this->_core->getWindow()->getReceiver();
    this->_back_ground = this->_driver->getTexture("./assets/HOW_BG.png");
    this->_back_button_gui = nullptr;
    this->_back_button_pre_tx = this->_driver->getTexture("./assets/BACK_PRE.png");
    this->_back_button_post_tx = this->_driver->getTexture("./assets/BACK_POST.png");
    this->_back_button_hover_tx = this->_driver->getTexture("./assets/BACK_HOVER.png");
}

HowMenu::~HowMenu()
{
    this->_gui->clear();
}

void HowMenu::createButtons()
{
    this->_back_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(1900 / 3 + 500, 1080 / 3 + 550, 1900 / 2.1 + 500, 1080 / 2.6 + 550));
    this->_back_button_gui->setImage(this->_back_button_pre_tx);
    this->_back_button_gui->setPressedImage(this->_back_button_post_tx);
    this->_back_button_gui->setScaleImage();
    this->_back_button_gui->setIsPushButton();
    this->_current_button = std::make_tuple(0, 0, this->_back_button_gui, this->_back_button_pre_tx, this->_back_button_hover_tx);
}

int HowMenu::buttonAction()
{
    if (this->_back_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_core->setBackToMainMenu(true);
        this->_back_button_gui->setPressed(false);
        return EXIT;
    }
    return DEFAULT;
}

std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>HowMenu::checkNextButton(int x, int y)
{
    return this->_current_button;
}

void HowMenu::drawBackground()
{
    this->_driver->draw2DImage(this->_back_ground, irr::core::rect<irr::s32>(0, 0, this->_core->getWindow()->getWidth(), this->_core->getWindow()->getHeight()), irr::core::rect<irr::s32>(0, 0, BG_WIDTH, BG_HEIGHT));
}

void HowMenu::stopMenu()
{
    this->_stop = EXIT;
}

void HowMenu::useMenuEvents()
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
        this->_back_button_gui->setPressed(true);
}

void HowMenu::run()
{
    createButtons();
    while (this->_device->run() && this->_stop != EXIT) {
        this->_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
        drawBackground();
        useMenuEvents();
        this->_stop = buttonAction();
        this->_smgr->drawAll();
        this->_gui->drawAll();
        this->_driver->endScene();
    }
}

void HowMenu::splashScreen()
{
}