/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** defs
*/

#ifndef DEFS_HPP_
#define DEFS_HPP_

#include <../lib/irrlicht/include/irrlicht.h>
#include <../lib/irrklang/includes/irrKlang.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "Irrklang.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#define EXIT                    0
#define NEXT                    1
#define RESET                   2
#define _ERROR                  3
#define END                     4
#define DEFAULT                 -1

#define BG_WIDTH                1920
#define BG_HEIGHT               1080
#define ALL_PLAYER_TEXTURES     12

#define PLAYER                  1
#define IA                      2
#define NOTHING                 0
#define BASE_PATH               "./assets/player/"


#define SAVE_PATH   "./save/map_saved.txt"

#include <iostream>

#ifdef _WIN32
    #include <Windows.h>
    #define sleep(x) Sleep((x * 1000))
#else
    #include <unistd.h>
#endif

#include <vector>
#include <iostream>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>

#endif /* !DEFS_HPP_ */
