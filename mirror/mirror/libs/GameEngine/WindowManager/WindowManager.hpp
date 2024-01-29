/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** WindowManager
*/

#ifndef WINDOWMANAGER_HPP_
#define WINDOWMANAGER_HPP_

#include <SFML/Graphics.hpp>

class WindowManager {
public:
    void create(int width, int height, int windowFramerateLimit, const std::string& title);
    void clear();
    void display();
    void close();
    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow window;
};

#endif /* !WINDOWMANAGER_HPP_ */
