/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "defs.hpp"
#include "Core.hpp"
#include "Music.hpp"
#include "Time.hpp"

int main()
{
    /* try { */
        Core core;
        core.runSplashScreen();
        core.runMainMenu();
    /* } catch (std::exception e) {
        std::cout << e.what() << std::endl;
        return 84;
    } */
    return 0;
}