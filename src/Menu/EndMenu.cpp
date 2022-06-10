/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EndMenu
*/

#include "Core.hpp"
#include "EndMenu.hpp"

EndMenu::EndMenu(Core *core, int player_id)
{
    this->_core = core;
    this->_player_id = player_id;
    this->_stop = DEFAULT;
    this->_device = this->_core->getWindow()->getDevice();
    this->_driver = this->_core->getWindow()->getDriver();
    this->_smgr = this->_core->getWindow()->getSmgr();
    this->_gui = this->_core->getWindow()->getGui();
    this->_receiver = this->_core->getWindow()->getReceiver();
    this->_again_button_gui = nullptr;
    this->_back_ground = this->_driver->getTexture("./assets/BACK.png");
    this->_again_button_pre_tx = this->_driver->getTexture("./assets/AGAIN_PRE.png");
    this->_again_button_post_tx = this->_driver->getTexture("./assets/AGAIN_POST.png");
    this->_again_button_hover_tx = this->_driver->getTexture("./assets/AGAIN_HOVER.png");
    this->_quit_button_gui = nullptr;
    this->_quit_button_pre_tx = this->_driver->getTexture("./assets/QUIT_PRE.png");
    this->_quit_button_post_tx = this->_driver->getTexture("./assets/QUIT_POST.png");
    this->_quit_button_hover_tx = this->_driver->getTexture("./assets/QUIT_HOVER.png");
    this->_main_button_gui = nullptr;
    this->_main_button_pre_tx = this->_driver->getTexture("./assets/MAIN_MENU_PRE.png");
    this->_main_button_post_tx = this->_driver->getTexture("./assets/MAIN_MENU_POST.png");
    this->_main_button_hover_tx = this->_driver->getTexture("./assets/MAIN_MENU_HOVER.png");
    std::string str =  "Steve " + std::to_string(player_id) + " wins !";
    std::wstring widestr = std::wstring(str.begin(), str.end());
    if (player_id == 0)
        widestr = std::wstring(L"        Draw !");
    this->_text_end_game = this->_device->getGUIEnvironment()->addStaticText(widestr.c_str(), irr::core::rect<irr::s32>(130,20,1000,150));
    this->_text_end_game->setOverrideFont(this->_core->getWindow()->getFont72());
    this->_text_end_game->setRelativePosition(irr::core::position2d<irr::s32>(700,40));
    this->_text_end_game->setOverrideColor(irr::video::SColor(255,255,255,255));
}

EndMenu::~EndMenu()
{
    this->_gui->clear();
}

void EndMenu::createButtons()
{
    this->_again_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3, this->_core->getWindow()->getHeight() / 3 + 280, this->_core->getWindow()->getWidth() / 1.5, this->_core->getWindow()->getHeight() / 2.6 + 280));
    this->_again_button_gui->setImage(this->_again_button_pre_tx);
    this->_again_button_gui->setPressedImage(this->_again_button_post_tx);
    this->_again_button_gui->setScaleImage();
    this->_again_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 0, this->_again_button_gui, this->_again_button_pre_tx, this->_again_button_hover_tx));
    this->_current_button = std::make_tuple(0, 0, this->_again_button_gui, this->_again_button_pre_tx, this->_again_button_hover_tx);
    this->_quit_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3, this->_core->getWindow()->getHeight() / 3 + 360, this->_core->getWindow()->getWidth() / 2.1, this->_core->getWindow()->getHeight() / 2.6 + 360));
    this->_quit_button_gui->setImage(this->_quit_button_pre_tx);
    this->_quit_button_gui->setPressedImage(this->_quit_button_post_tx);
    this->_quit_button_gui->setScaleImage();
    this->_quit_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 0, this->_quit_button_gui, this->_quit_button_pre_tx, this->_quit_button_hover_tx));
    this->_main_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3 + 361, this->_core->getWindow()->getHeight() / 3 + 360, this->_core->getWindow()->getWidth() / 1.5, this->_core->getWindow()->getHeight() / 2.6 + 360));
    this->_main_button_gui->setImage(this->_main_button_pre_tx);
    this->_main_button_gui->setPressedImage(this->_main_button_post_tx);
    this->_main_button_gui->setScaleImage();
    this->_main_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 1, this->_main_button_gui, this->_main_button_pre_tx, this->_main_button_hover_tx));
}

int EndMenu::buttonAction()
{
    if (this->_again_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_core->setCharacterMenu(true);
        this->_again_button_gui->setPressed(false);
        return EXIT;
    }
    if (this->_quit_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_quit_button_gui->setPressed(false);
        return EXIT;
    }
    if (this->_main_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_core->setBackToMainMenu(true);
        this->_main_button_gui->setPressed(false);
        return EXIT;
    }
    return DEFAULT;
}

std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>EndMenu::checkNextButton(int x, int y)
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

void EndMenu::useMenuEvents()
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

void EndMenu::drawBackground()
{
    this->_driver->draw2DImage(this->_back_ground, irr::core::rect<irr::s32>(0, 0, this->_core->getWindow()->getWidth(), this->_core->getWindow()->getHeight()), irr::core::rect<irr::s32>(0, 0, BG_WIDTH, BG_HEIGHT));
}

void EndMenu::stopMenu()
{
    this->_stop = EXIT;
}

void EndMenu::run()
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

void EndMenu::splashScreen()
{
}