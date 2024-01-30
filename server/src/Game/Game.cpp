/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Game
*/

#include "../../include/Game/Game.hpp"

Game::Game()
{
    this->isStarted = false;
}

Game::~Game() {}

void Game::setStarted(bool state)
{
    this->isStarted = state;
}

bool Game::hasStarted()
{
    return (this->isStarted);
}
