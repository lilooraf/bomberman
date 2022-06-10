/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Music
*/

#include "Music.hpp"

Music::Music()
{
    this->_engine = irrklang::createIrrKlangDevice();
    if (!this->_engine)
        throw std::runtime_error("Sound Engine cannot be loaded");
    this->_stopM = false;
    this->_muteM = false;
    this->_muteS = false;
}

Music::~Music()
{
    this->_engine->drop();
}

void Music::stopMusic()
{
    this->_engine->stopAllSounds();
    this->_stopM = false;
}

void Music::pauseMusic(bool pause) const
{
    this->_engine->setAllSoundsPaused(pause);
}

void Music::muteMusic()
{
    this->_muteM = true;
    this->_stopM = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Music::muteSound()
{
    this->_muteS = true;
}

void Music::unmuteMusic()
{
    this->_muteM = false;
}

void Music::unmuteSound()
{
    this->_muteS = false;
}

void Music::loadSound(std::string path, int time)
{
    std::string full_path = "./assets/music/" + path + ".ogg";

    if (this->_muteS == true)
        return;
    time *= 1000;
    std::thread thread = std::thread([&, time, full_path]() {
        this->_engine->play2D(full_path.c_str(), false);
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    });
    thread.detach();
}

void Music::loadMusic(std::string path)
{
    std::string full_path = "./assets/music/" + path + ".ogg";

    if (this->_muteM == true)
        return;
    if (this->_stopM == true) {
        this->_stopM = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->_stopM = true;
    } else {
        this->_stopM = true;
    }
    std::thread thread = std::thread([&, full_path]() {
        this->_engine->play2D(full_path.c_str(), true);
        while (this->_stopM);
    });
    thread.detach();
}

bool Music::isMusicPlaying()
{
    return this->_stopM;
}