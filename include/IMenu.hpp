/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IMenu
*/

#ifndef IMENU_HPP_
#define IMENU_HPP_

class IMenu {
    public:
        virtual ~IMenu() {};

        virtual void run() = 0;
        virtual void splashScreen() = 0;
        virtual void stopMenu() = 0;
        virtual void useMenuEvents() = 0;
        virtual int buttonAction() = 0;
        virtual void drawBackground() = 0;
    protected:
    private:
};

#endif /* !IMENU_HPP_ */
