/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenu
*/

#include "Core.hpp"
#include "MainMenu.hpp"

MainMenu::MainMenu(Core *core)
{
    this->_core = core;
    this->_stop = DEFAULT;
    this->_device = this->_core->getWindow()->getDevice();
    this->_driver = this->_core->getWindow()->getDriver();
    this->_smgr = this->_core->getWindow()->getSmgr();
    this->_gui = this->_core->getWindow()->getGui();
    this->_receiver = this->_core->getWindow()->getReceiver();
    this->_over = this->_driver->getTexture("./assets/hover_button.png");
    this->_disabled_tx = this->_driver->getTexture("./assets/LOAD_DISABLE.png");
    this->_splash_tx = this->_driver->getTexture("./assets/LOGO.png");
    this->_back_ground = this->_driver->getTexture("./assets/BACKGROUND.png");
    this->_new_button_gui = nullptr;
    this->_new_button_pre_tx = this->_driver->getTexture("./assets/NEWGAME_PRE.png");
    this->_new_button_post_tx = this->_driver->getTexture("./assets/NEWGAME_POST.png");
    this->_new_button_hover_tx = this->_driver->getTexture("./assets/NEW_HOVER.png");
    this->_load_button_gui = nullptr;
    this->_load_button_pre_tx = this->_driver->getTexture("./assets/LOADGAME_PRE.png");
    this->_load_button_post_tx = this->_driver->getTexture("./assets/LOADGAME_POST.png");
    this->_load_button_hover_tx = this->_driver->getTexture("./assets/LOAD_HOVER.png");
    this->_option_button_gui = nullptr;
    this->_option_button_pre_tx = this->_driver->getTexture("./assets/OPTION_PRE.png");
    this->_option_button_post_tx = this->_driver->getTexture("./assets/OPTION_POST.png");
    this->_option_button_hover_tx = this->_driver->getTexture("./assets/OPTION_HOVER.png");
    this->_quit_button_gui = nullptr;
    this->_quit_button_pre_tx = this->_driver->getTexture("./assets/QUIT_PRE.png");
    this->_quit_button_post_tx = this->_driver->getTexture("./assets/QUIT_POST.png");
    this->_quit_button_hover_tx = this->_driver->getTexture("./assets/QUIT_HOVER.png");
    this->_how_button_gui = nullptr;
    this->_how_button_pre_tx = this->_driver->getTexture("./assets/HOW_PRE.png");
    this->_how_button_post_tx = this->_driver->getTexture("./assets/HOW_POST.png");
    this->_how_button_hover_tx = this->_driver->getTexture("./assets/HOW_HOVER.png");
    this->_credit_button_gui = nullptr;
    this->_credit_button_pre_tx = this->_driver->getTexture("./assets/CREDIT_PRE.png");
    this->_credit_button_post_tx = this->_driver->getTexture("./assets/CREDIT_POST.png");
    this->_credit_button_hover_tx = this->_driver->getTexture("./assets/CREDIT_HOVER.png");
}

MainMenu::~MainMenu()
{
    this->_gui->clear();
}

void MainMenu::createButtons()
{
    this->_new_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3, this->_core->getWindow()->getHeight() / 3, this->_core->getWindow()->getWidth() / 1.5, this->_core->getWindow()->getHeight() / 2.6));
    this->_new_button_gui->setImage(this->_new_button_pre_tx);
    this->_new_button_gui->setPressedImage(this->_new_button_post_tx);
    this->_new_button_gui->setScaleImage();
    this->_new_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 0, this->_new_button_gui, this->_new_button_pre_tx, this->_new_button_hover_tx));
    this->_current_button = std::make_tuple(0, 0, this->_new_button_gui, this->_new_button_pre_tx, this->_new_button_hover_tx);
    this->_load_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3, this->_core->getWindow()->getHeight() / 3 + 80, this->_core->getWindow()->getWidth() / 1.5, this->_core->getWindow()->getHeight() / 2.6 + 80));
    this->_load_button_gui->setImage(this->_load_button_pre_tx);
    this->_load_button_gui->setPressedImage(this->_load_button_post_tx);
    this->_load_button_gui->setScaleImage();
    this->_load_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 0, this->_load_button_gui, this->_load_button_pre_tx, this->_load_button_hover_tx));
    this->_option_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3, this->_core->getWindow()->getHeight() / 3 + 160, this->_core->getWindow()->getWidth() / 2.1, this->_core->getWindow()->getHeight() / 2.6 + 160));
    this->_option_button_gui->setImage(this->_option_button_pre_tx);
    this->_option_button_gui->setPressedImage(this->_option_button_post_tx);
    this->_option_button_gui->setScaleImage();
    this->_option_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(2, 0, this->_option_button_gui, this->_option_button_pre_tx, this->_option_button_hover_tx));
    this->_quit_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3 + 361, this->_core->getWindow()->getHeight() / 3 + 160, this->_core->getWindow()->getWidth() / 2.1 + 361, this->_core->getWindow()->getHeight() / 2.6 + 160));
    this->_quit_button_gui->setImage(this->_quit_button_pre_tx);
    this->_quit_button_gui->setPressedImage(this->_quit_button_post_tx);
    this->_quit_button_gui->setScaleImage();
    this->_quit_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(2, 1, this->_quit_button_gui, this->_quit_button_pre_tx, this->_quit_button_hover_tx));
    this->_how_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3 + 900, this->_core->getWindow()->getHeight() / 3 + 525, this->_core->getWindow()->getWidth() / 2.1 + 900, this->_core->getWindow()->getHeight() / 2.6 + 525));
    this->_how_button_gui->setImage(this->_how_button_pre_tx);
    this->_how_button_gui->setPressedImage(this->_how_button_post_tx);
    this->_how_button_gui->setScaleImage();
    this->_how_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(3, 1, this->_how_button_gui, this->_how_button_pre_tx, this->_how_button_hover_tx));
    this->_credit_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3 + 900, this->_core->getWindow()->getHeight() / 3 + 600, this->_core->getWindow()->getWidth() / 2.1 + 900, this->_core->getWindow()->getHeight() / 2.6 + 600));
    this->_credit_button_gui->setImage(this->_credit_button_pre_tx);
    this->_credit_button_gui->setPressedImage(this->_credit_button_post_tx);
    this->_credit_button_gui->setScaleImage();
    this->_credit_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(4, 1, this->_credit_button_gui, this->_credit_button_pre_tx, this->_credit_button_hover_tx));
}

int MainMenu::buttonAction()
{
    if (this->_new_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_core->setLoad(false);
        this->_core->setCharacterMenu(true);
        this->_new_button_gui->setPressed(false);
        return NEXT;
    }
    if (this->_load_button_gui->isPressed() && this->_load_button_gui->isEnabled()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_core->setLoad(true);
        this->_core->setCharacterMenu(true);
        this->_load_button_gui->setPressed(false);
        return NEXT;
    }
    if (this->_option_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_core->setSettingsMenu(true);
        this->_option_button_gui->setPressed(false);
        return EXIT;
    }
    if (this->_how_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_core->setHowMenu(true);
        this->_how_button_gui->setPressed(false);
        return NEXT;
    }
    if (this->_credit_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_core->setCreditMenu(true);
        this->_credit_button_gui->setPressed(false);
        return NEXT;
    }
    if (this->_quit_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_quit_button_gui->setPressed(false);
        return EXIT;
    }
    return DEFAULT;
}

std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>MainMenu::checkNextButton(int x, int y)
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
    for (int i = y; i < 10; i++) {
        for (std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *> button : this->_button_array) {
            if (std::get<0>(button) == x && std::get<1>(button) == i) {
                if (!std::get<2>(button)->isEnabled()) {
                    return checkNextButton(x + (x - std::get<0>(this->_current_button)), y + (y - std::get<1>(this->_current_button)));
                } else
                    return button;
            }
        }
    }
    return this->_current_button;
}

void MainMenu::useMenuEvents()
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
        this->_quit_button_gui->setPressed(true);
}

void MainMenu::drawBackground()
{
    this->_driver->draw2DImage(this->_back_ground, irr::core::rect<irr::s32>(0, 0, this->_core->getWindow()->getWidth(), this->_core->getWindow()->getHeight()), irr::core::rect<irr::s32>(0, 0, BG_WIDTH, BG_HEIGHT));
}

void MainMenu::stopMenu()
{
    this->_stop = EXIT;
}

void MainMenu::run()
{
    createButtons();
    while (this->_device->run() && this->_stop != EXIT && this->_stop != NEXT) {
        if (!this->_core->checkIfLoadable()) {
            this->_load_button_gui->setImage(this->_disabled_tx);
            this->_load_button_gui->setEnabled(false);
        } else
            this->_load_button_gui->setImage(this->_load_button_pre_tx);
        this->_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
        drawBackground();
        useMenuEvents();
        this->_stop = buttonAction();
        this->_smgr->drawAll();
        this->_gui->drawAll();
        this->_driver->endScene();
    }
}

void MainMenu::splashScreen()
{
    this->_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));  
    this->_driver->draw2DImage(this->_splash_tx, irr::core::rect<irr::s32>(0, 0, this->_core->getWindow()->getWidth(), this->_core->getWindow()->getHeight()), irr::core::rect<irr::s32>(0, 0, BG_WIDTH, BG_HEIGHT));
    this->_gui->drawAll();
    this->_driver->endScene();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}