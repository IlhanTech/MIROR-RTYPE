/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <thread>

class Game {
    public:
        Game();
        ~Game();
        void setStarted(bool state);
        bool hasStarted();

    private:
        std::vector<std::reference_wrapper<std::thread>> connectionThreads;
        bool isStarted;
};

#endif /* !GAME_HPP_ */
