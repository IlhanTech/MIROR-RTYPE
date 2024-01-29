/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** WindowManager
*/

#include "WindowManager.hpp"

void WindowManager::create(int width, int height,  int windowFramerateLimit,const std::string& title)
{
    window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(windowFramerateLimit);
}

void WindowManager::clear()
{
    window.clear();
}

void WindowManager::display()
{
    window.display();
}

void WindowManager::close()
{
    window.close();
}

sf::RenderWindow& WindowManager::getWindow()
{
    return window;
}
