/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Music
*/

#include "defs.hpp"

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

class Music {
    public:
        Music();
        ~Music();
        void loadSound(std::string path, int sleep);
        void loadMusic(std::string path);
        void stopMusic();
        void muteMusic();
        void muteSound();
        void unmuteMusic();
        void unmuteSound();
        void pauseMusic(bool pause) const;
        bool isMusicPlaying();
    protected:
    private:
        bool _stopM;
        bool _muteM;
        bool _muteS;
        irrklang::ISoundEngine *_engine;
};

#endif /* !MUSIC_HPP_ */
