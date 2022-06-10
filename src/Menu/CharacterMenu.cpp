/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterMenu
*/

#include "Core.hpp"
#include "CharacterMenu.hpp"

CharacterMenu::CharacterMenu(Core *core)
{
    this->_core = core;
    this->_stop = DEFAULT;
    this->_device = this->_core->getWindow()->getDevice();
    this->_driver = this->_core->getWindow()->getDriver();
    this->_smgr = this->_core->getWindow()->getSmgr();
    this->_gui = this->_core->getWindow()->getGui();
    this->_smgr = this->_device->getSceneManager();
    this->_back_ground_tx = this->_driver->getTexture("./assets/CHARACTER_MENU_BG.png");
    this->_left_pre_tx = this->_driver->getTexture("./assets/LEFT_PRE.png");
    this->_left_post_tx = this->_driver->getTexture("./assets/LEFT_POST.png");
    this->_left_hover_tx = this->_driver->getTexture("./assets/LEFT_HOVER.png");
    this->_right_pre_tx = this->_driver->getTexture("./assets/RIGHT_PRE.png");
    this->_right_post_tx = this->_driver->getTexture("./assets/RIGHT_POST.png");
    this->_right_hover_tx = this->_driver->getTexture("./assets/RIGHT_HOVER.png");
    this->_play_button_gui = nullptr;
    this->_play_button_pre_tx = this->_driver->getTexture("./assets/PLAY_PRE.png");
    this->_play_button_post_tx = this->_driver->getTexture("./assets/PLAY_POST.png");
    this->_play_button_hover_tx = this->_driver->getTexture("./assets/PLAY_HOVER.png");
    this->_back_button_gui = nullptr;
    this->_back_button_pre_tx = this->_driver->getTexture("./assets/BACK_PRE.png");
    this->_back_button_post_tx = this->_driver->getTexture("./assets/BACK_POST.png");
    this->_back_button_hover_tx = this->_driver->getTexture("./assets/BACK_HOVER.png");
    loadAllPlayerTextures();
    initAllPlayers();
    this->_player_tx = this->_driver->getTexture("./assets/PLAYER.png");
    this->_ia_tx = this->_driver->getTexture("./assets/IA.png");
    this->_nothing_tx = this->_driver->getTexture("./assets/NOTHING.png");
}

CharacterMenu::~CharacterMenu()
{
    this->_gui->clear();
}

void CharacterMenu::initAllPlayers()
{
    this->_player1 = std::make_pair(PLAYER, this->_allPlayerTexture.at(1));
    this->_player2 = std::make_pair(PLAYER, this->_allPlayerTexture.at(2));
    this->_player3 = std::make_pair(IA, this->_allPlayerTexture.at(3));
    this->_player4 = std::make_pair(NOTHING, this->_allPlayerTexture.at(0));
}

std::string CharacterMenu::getTexturePath(std::string path)
{
    path.assign(BASE_PATH + path);
    return path;
}

irr::video::ITexture *CharacterMenu::loadTexture(std::string path)
{
    if (!path.empty())
        return this->_driver->getTexture(getTexturePath(path).c_str());
    else
        return nullptr;
}


void CharacterMenu::loadAllPlayerTextures()
{
    playerTexture_t playerTx;
    playerTx.id = 0;
    playerTx.tex = this->_driver->getTexture("./assets/player/NOTHING_PREV.png");
    this->_allPlayerTexture.push_back(playerTx);

    for (int i = 1; i < ALL_PLAYER_TEXTURES; i++) {
        playerTx.id = i;
        playerTx.tex = this->_driver->getTexture(getTexturePath(std::to_string(i).append("pathPrev.png")).c_str());
        this->_allPlayerTexture.push_back(playerTx);
    }
}

void CharacterMenu::createButtons1()
{
    this->_back_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3, this->_core->getWindow()->getHeight() / 3 + 550, this->_core->getWindow()->getWidth() / 2.1, this->_core->getWindow()->getHeight() / 2.6 + 550));
    this->_back_button_gui->setImage(this->_back_button_pre_tx);
    this->_back_button_gui->setPressedImage(this->_back_button_post_tx);
    this->_back_button_gui->setScaleImage();
    this->_back_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(2, 3, this->_back_button_gui, this->_back_button_pre_tx, this->_back_button_hover_tx));
    this->_play_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(this->_core->getWindow()->getWidth() / 3 + 361, this->_core->getWindow()->getHeight() / 3 + 550, this->_core->getWindow()->getWidth() / 2.1 + 361, this->_core->getWindow()->getHeight() / 2.6 + 550));
    this->_play_button_gui->setImage(this->_play_button_pre_tx);
    this->_play_button_gui->setPressedImage(this->_play_button_post_tx);
    this->_play_button_gui->setScaleImage();
    this->_play_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(2, 4, this->_play_button_gui, this->_play_button_pre_tx, this->_play_button_hover_tx));
    this->_current_button = std::make_tuple(2, 4, this->_play_button_gui, this->_play_button_pre_tx, this->_play_button_hover_tx);

    this->_right1_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(375 + 240 * 0, 500, 425 + 240 * 0, 550));
    this->_right1_button_gui->setImage(this->_right_pre_tx);
    this->_right1_button_gui->setPressedImage(this->_right_post_tx);
    this->_right1_button_gui->setScaleImage();
    this->_right1_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 1, this->_right1_button_gui, this->_right_pre_tx, this->_right_hover_tx));

    this->_right2_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(375 + 240 * 2, 500, 425 + 240 * 2, 550));
    this->_right2_button_gui->setImage(this->_right_pre_tx);
    this->_right2_button_gui->setPressedImage(this->_right_post_tx);
    this->_right2_button_gui->setScaleImage();
    this->_right2_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 3, this->_right2_button_gui, this->_right_pre_tx, this->_right_hover_tx));

    this->_right3_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(375 + 240 * 4, 500, 425 + 240 * 4, 550));
    this->_right3_button_gui->setImage(this->_right_pre_tx);
    this->_right3_button_gui->setPressedImage(this->_right_post_tx);
    this->_right3_button_gui->setScaleImage();
    this->_right3_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 5, this->_right3_button_gui, this->_right_pre_tx, this->_right_hover_tx));

    this->_right4_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(375 + 240 * 6, 500, 425 + 240 * 6, 550));
    this->_right4_button_gui->setImage(this->_right_pre_tx);
    this->_right4_button_gui->setPressedImage(this->_right_post_tx);
    this->_right4_button_gui->setScaleImage();
    this->_right4_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 7, this->_right4_button_gui, this->_right_pre_tx, this->_right_hover_tx));
}

void CharacterMenu::createButtons2()
{
    this->_right5_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(375 + 240 * 0, 792, 425 + 240 * 0, 842));
    this->_right5_button_gui->setImage(this->_right_pre_tx);
    this->_right5_button_gui->setPressedImage(this->_right_post_tx);
    this->_right5_button_gui->setScaleImage();
    this->_right5_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 1, this->_right5_button_gui, this->_right_pre_tx, this->_right_hover_tx));

    this->_right6_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(375 + 240 * 2, 792, 425 + 240 * 2, 842));
    this->_right6_button_gui->setImage(this->_right_pre_tx);
    this->_right6_button_gui->setPressedImage(this->_right_post_tx);
    this->_right6_button_gui->setScaleImage();
    this->_right6_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 3, this->_right6_button_gui, this->_right_pre_tx, this->_right_hover_tx));

    this->_right7_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(375 + 240 * 4, 792, 425 + 240 * 4, 842));
    this->_right7_button_gui->setImage(this->_right_pre_tx);
    this->_right7_button_gui->setPressedImage(this->_right_post_tx);
    this->_right7_button_gui->setScaleImage();
    this->_right7_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 5, this->_right7_button_gui, this->_right_pre_tx, this->_right_hover_tx));

    this->_right8_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(375 + 240 * 6, 792, 425 + 240 * 6, 842));
    this->_right8_button_gui->setImage(this->_right_pre_tx);
    this->_right8_button_gui->setPressedImage(this->_right_post_tx);
    this->_right8_button_gui->setScaleImage();
    this->_right8_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 7, this->_right8_button_gui, this->_right_pre_tx, this->_right_hover_tx));

    this->_left1_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(75 + 240 * 0, 500, 125 + 240 * 0, 550));
    this->_left1_button_gui->setImage(this->_left_pre_tx);
    this->_left1_button_gui->setPressedImage(this->_left_post_tx);
    this->_left1_button_gui->setScaleImage();
    this->_left1_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 0, this->_left1_button_gui, this->_left_pre_tx, this->_left_hover_tx));

    this->_left2_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(75 + 240 * 2, 500, 125 + 240 * 2, 550));
    this->_left2_button_gui->setImage(this->_left_pre_tx);
    this->_left2_button_gui->setPressedImage(this->_left_post_tx);
    this->_left2_button_gui->setScaleImage();
    this->_left2_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 2, this->_left2_button_gui, this->_left_pre_tx, this->_left_hover_tx));
}

void CharacterMenu::createButtons3()
{

    this->_left3_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(75 + 240 * 4, 500, 125 + 240 * 4, 550));
    this->_left3_button_gui->setImage(this->_left_pre_tx);
    this->_left3_button_gui->setPressedImage(this->_left_post_tx);
    this->_left3_button_gui->setScaleImage();
    this->_left3_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 4, this->_left3_button_gui, this->_left_pre_tx, this->_left_hover_tx));

    this->_left4_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(75 + 240 * 6, 500, 125 + 240 * 6, 550));
    this->_left4_button_gui->setImage(this->_left_pre_tx);
    this->_left4_button_gui->setPressedImage(this->_left_post_tx);
    this->_left4_button_gui->setScaleImage();
    this->_left4_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(0, 6, this->_left4_button_gui, this->_left_pre_tx, this->_left_hover_tx));

    this->_left5_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(75 + 240 * 0, 792, 125 + 240 * 0, 842));
    this->_left5_button_gui->setImage(this->_left_pre_tx);
    this->_left5_button_gui->setPressedImage(this->_left_post_tx);
    this->_left5_button_gui->setScaleImage();
    this->_left5_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 0, this->_left5_button_gui, this->_left_pre_tx, this->_left_hover_tx));

    this->_left6_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(75 + 240 * 2, 792, 125 + 240 * 2, 842));
    this->_left6_button_gui->setImage(this->_left_pre_tx);
    this->_left6_button_gui->setPressedImage(this->_left_post_tx);
    this->_left6_button_gui->setScaleImage();
    this->_left6_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 2, this->_left6_button_gui, this->_left_pre_tx, this->_left_hover_tx));

    this->_left7_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(75 + 240 * 4, 792, 125 + 240 * 4, 842));
    this->_left7_button_gui->setImage(this->_left_pre_tx);
    this->_left7_button_gui->setPressedImage(this->_left_post_tx);
    this->_left7_button_gui->setScaleImage();
    this->_left7_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 4, this->_left7_button_gui, this->_left_pre_tx, this->_left_hover_tx));

    this->_left8_button_gui = this->_gui->addButton(irr::core::rect<irr::s32>(75 + 240 * 6, 792, 125 + 240 * 6, 842));
    this->_left8_button_gui->setImage(this->_left_pre_tx);
    this->_left8_button_gui->setPressedImage(this->_left_post_tx);
    this->_left8_button_gui->setScaleImage();
    this->_left8_button_gui->setIsPushButton();
    this->_button_array.push_back(std::make_tuple(1, 6, this->_left8_button_gui, this->_left_pre_tx, this->_left_hover_tx));
}

std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *>CharacterMenu::checkNextButton(int x, int y)
{
    for (std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *> button : this->_button_array) {
        if (std::get<0>(button) == x && std::get<1>(button) == y) {
            if (!std::get<2>(button)->isEnabled()) {
                return checkNextButton(x + (x - std::get<0>(this->_current_button)), y + (y - std::get<1>(this->_current_button)));
            } else
                return button;
        }
    }
    for (int i = y; i >= 0; i--) {
        for (std::tuple<int, int, irr::gui::IGUIButton *, irr::video::ITexture *, irr::video::ITexture *> button : this->_button_array) {
            if (std::get<0>(button) == x && std::get<1>(button) == i) {
                if (!std::get<2>(button)->isEnabled()) {
                    return checkNextButton(x + (x - std::get<0>(this->_current_button)), y + (y - std::get<1>(this->_current_button)));
                } else
                    return button;
            }
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

int CharacterMenu::buttonAction()
{
    int good = 0;
    if (this->_play_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player1.first > 0)
            good++;
        if (this->_player2.first > 0)
            good++;
        if (this->_player3.first > 0)
            good++;
        if (this->_player4.first > 0)
            good++;
        if (good < 2) {
            this->_play_button_gui->setPressed(false);
            return DEFAULT;
        }
        this->_core->pushBackInPlayers(this->_player1);
        this->_core->pushBackInPlayers(this->_player2);
        this->_core->pushBackInPlayers(this->_player3);
        this->_core->pushBackInPlayers(this->_player4);
        this->_core->setGameRunning(true);
        return NEXT;
    }
    if (this->_back_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        this->_back_button_gui->setPressed(false);
        return EXIT;
    }
    buttonActionPlayer1();
    buttonActionPlayer2();
    buttonActionPlayer3();
    buttonActionPlayer4();
    return DEFAULT;
}

int CharacterMenu::buttonActionPlayer1()
{
    if (this->_left1_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player1.second.id > 2 && this->_player1.second.id != 0)
            this->_player1.second = this->_allPlayerTexture.at(this->_player1.second.id - 1);
        else if (this->_player1.second.id != 0)
            this->_player1.second = this->_allPlayerTexture.at(ALL_PLAYER_TEXTURES - 1);
        this->_left1_button_gui->setPressed(false);
    }
    if (this->_right1_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player1.second.id == 0);
        else if (this->_player1.second.id < ALL_PLAYER_TEXTURES - 1)
            this->_player1.second = this->_allPlayerTexture.at(this->_player1.second.id + 1);
        else
            this->_player1.second = this->_allPlayerTexture.at(1);
        this->_right1_button_gui->setPressed(false);
    }
    if (this->_left5_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player1.first > NOTHING)
            this->_player1.first--;
        else
            this->_player1.first = IA;
        this->_left5_button_gui->setPressed(false);
    }
    if (this->_right5_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player1.first < IA)
            this->_player1.first++;
        else
            this->_player1.first = NOTHING;
        this->_right5_button_gui->setPressed(false);
    }
    return DEFAULT;
}

int CharacterMenu::buttonActionPlayer2()
{
    if (this->_left2_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player2.second.id > 2)
            this->_player2.second = this->_allPlayerTexture.at(this->_player2.second.id - 1);
        else if (this->_player2.second.id != 0)
            this->_player2.second = this->_allPlayerTexture.at(ALL_PLAYER_TEXTURES - 1);
        this->_left2_button_gui->setPressed(false);
    }
    if (this->_right2_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player2.second.id == 0);
        else if (this->_player2.second.id < ALL_PLAYER_TEXTURES - 1)
            this->_player2.second = this->_allPlayerTexture.at(this->_player2.second.id + 1);
        else
            this->_player2.second = this->_allPlayerTexture.at(1);
        this->_right2_button_gui->setPressed(false);
    }
    if (this->_left6_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player2.first > NOTHING)
            this->_player2.first--;
        else
            this->_player2.first = IA;
        this->_left6_button_gui->setPressed(false);
    }
    if (this->_right6_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player2.first < IA)
            this->_player2.first++;
        else
            this->_player2.first = NOTHING;
        this->_right6_button_gui->setPressed(false);
    }
    return DEFAULT;
}

int CharacterMenu::buttonActionPlayer3()
{
    if (this->_left3_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player3.second.id > 2)
            this->_player3.second = this->_allPlayerTexture.at(this->_player3.second.id - 1);
        else if (this->_player3.second.id != 0)
            this->_player3.second = this->_allPlayerTexture.at(ALL_PLAYER_TEXTURES - 1);
        this->_left3_button_gui->setPressed(false);
    }
    if (this->_right3_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player3.second.id == 0);
        else if (this->_player3.second.id < ALL_PLAYER_TEXTURES - 1)
            this->_player3.second = this->_allPlayerTexture.at(this->_player3.second.id + 1);
        else
            this->_player3.second = this->_allPlayerTexture.at(1);
        this->_right3_button_gui->setPressed(false);
    }
    if (this->_left7_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player3.first > NOTHING)
            this->_player3.first--;
        else
            this->_player3.first = IA;
        this->_left7_button_gui->setPressed(false);
    }
    if (this->_right7_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player3.first < IA)
            this->_player3.first++;
        else
            this->_player3.first = NOTHING;
        this->_right7_button_gui->setPressed(false);
    }
    return DEFAULT;
}

int CharacterMenu::buttonActionPlayer4()
{
    if (this->_left4_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player4.second.id > 1)
            this->_player4.second = this->_allPlayerTexture.at(this->_player4.second.id - 1);
        else if (this->_player4.second.id != 0)
            this->_player4.second = this->_allPlayerTexture.at(ALL_PLAYER_TEXTURES - 1);
        this->_left4_button_gui->setPressed(false);
    }
    if (this->_right4_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player4.second.id == 0);
        else if (this->_player4.second.id < ALL_PLAYER_TEXTURES - 1)
            this->_player4.second = this->_allPlayerTexture.at(this->_player4.second.id + 1);
        else
            this->_player4.second = this->_allPlayerTexture.at(1);
        this->_right4_button_gui->setPressed(false);
    }
    if (this->_left8_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player4.first > NOTHING)
            this->_player4.first--;
        else
            this->_player4.first = IA;
        this->_left8_button_gui->setPressed(false);
    }
    if (this->_right8_button_gui->isPressed()) {
        this->_core->getMusic()->loadSound("click", 1);
        if (this->_player4.first < IA)
            this->_player4.first++;
        else
            this->_player4.first = NOTHING;
        this->_right8_button_gui->setPressed(false);
    }
    return DEFAULT;
}

void CharacterMenu::drawBackground()
{
    this->_driver->draw2DImage(this->_back_ground_tx, irr::core::rect<irr::s32>(0, 0, this->_core->getWindow()->getWidth(), this->_core->getWindow()->getHeight()), irr::core::rect<irr::s32>(0, 0, BG_WIDTH, BG_HEIGHT));
}

void CharacterMenu::useMenuEvents()
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

void CharacterMenu::createImages()
{
    this->_little_img1 = this->_gui->addImage(irr::core::rect<irr::s32>(200, 750, 300, 850));
    this->_little_img2 = this->_gui->addImage(irr::core::rect<irr::s32>(200 + 240 * 2, 750, 300 + 240 * 2, 850));
    this->_little_img3 = this->_gui->addImage(irr::core::rect<irr::s32>(200 + 240 * 4, 750, 300 + 240 * 4, 850));
    this->_little_img4 = this->_gui->addImage(irr::core::rect<irr::s32>(200 + 240 * 6, 750, 300 + 240 * 6, 850));

    this->_prev_img1 = this->_gui->addImage(irr::core::rect<irr::s32>(150, 350, 350, 700));
    this->_prev_img2 = this->_gui->addImage(irr::core::rect<irr::s32>(150 + 240 * 2, 350, 350 + 240 * 2, 700));
    this->_prev_img3 = this->_gui->addImage(irr::core::rect<irr::s32>(150 + 240 * 4, 350, 350 + 240 * 4, 700));
    this->_prev_img4 = this->_gui->addImage(irr::core::rect<irr::s32>(150 + 240 * 6, 350, 350 + 240 * 6, 700));
}

void CharacterMenu::setLittleImages()
{
    if (this->_player1.first == NOTHING) {
        this->_little_img1->setImage(this->_nothing_tx);
        this->_little_img1->setScaleImage(true);
    } else if (this->_player1.first == PLAYER) {
        this->_little_img1->setImage(this->_player_tx);
        this->_little_img1->setScaleImage(true);
    } else
        this->_little_img1->setImage(this->_ia_tx);
        this->_little_img1->setScaleImage(true);
    if (this->_player2.first == NOTHING) {
        this->_little_img2->setImage(this->_nothing_tx);
        this->_little_img2->setScaleImage(true);
    } else if (this->_player2.first == PLAYER) {
        this->_little_img2->setImage(this->_player_tx);
        this->_little_img2->setScaleImage(true);
    } else
        this->_little_img2->setImage(this->_ia_tx);
        this->_little_img2->setScaleImage(true);
    if (this->_player3.first == NOTHING) {
        this->_little_img3->setImage(this->_nothing_tx);
        this->_little_img3->setScaleImage(true);
    } else if (this->_player3.first == PLAYER) {
        this->_little_img3->setImage(this->_player_tx);
        this->_little_img3->setScaleImage(true);
    } else
        this->_little_img3->setImage(this->_ia_tx);
        this->_little_img3->setScaleImage(true);
    if (this->_player4.first == NOTHING) {
        this->_little_img4->setImage(this->_nothing_tx);
        this->_little_img4->setScaleImage(true);
    } else if (this->_player4.first == PLAYER) {
        this->_little_img4->setImage(this->_player_tx);
        this->_little_img4->setScaleImage(true);
    } else
        this->_little_img4->setImage(this->_ia_tx);
        this->_little_img4->setScaleImage(true);
}

void CharacterMenu::setPrevImages()
{
    if (this->_player1.first == NOTHING)
        this->_player1.second = this->_allPlayerTexture.at(0);
    else if (this->_player1.second.id == 0)
        this->_player1.second = this->_allPlayerTexture.at(1);
    if (this->_player2.first == NOTHING)
        this->_player2.second = this->_allPlayerTexture.at(0);
    else if (this->_player2.second.id == 0)
        this->_player2.second = this->_allPlayerTexture.at(1);
    if (this->_player3.first == NOTHING)
        this->_player3.second = this->_allPlayerTexture.at(0);
    else if (this->_player3.second.id == 0)
        this->_player3.second = this->_allPlayerTexture.at(1);
    if (this->_player4.first == NOTHING)
        this->_player4.second = this->_allPlayerTexture.at(0);
    else if (this->_player4.second.id == 0)
        this->_player4.second = this->_allPlayerTexture.at(1);
    this->_prev_img1->setImage(this->_player1.second.tex);
    this->_prev_img1->setScaleImage(true);
    this->_prev_img2->setImage(this->_player2.second.tex);
    this->_prev_img2->setScaleImage(true);
    this->_prev_img3->setImage(this->_player3.second.tex);
    this->_prev_img3->setScaleImage(true);
    this->_prev_img4->setImage(this->_player4.second.tex);
    this->_prev_img4->setScaleImage(true);
}

void CharacterMenu::run()
{
    createButtons1();
    createButtons2();
    createButtons3();
    createImages();
    while (this->_device->run() && this->_stop != EXIT && this->_stop != NEXT) {
        this->_driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        drawBackground();
        useMenuEvents();
        setLittleImages();
        setPrevImages();
        this->_stop = buttonAction();
        this->_smgr->drawAll();
        this->_gui->drawAll();
        this->_driver->endScene();
    }
}

void CharacterMenu::splashScreen()
{
}

void CharacterMenu::stopMenu()
{
    this->_stop = EXIT;
}