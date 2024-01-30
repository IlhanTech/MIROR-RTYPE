/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** GameConfig
*/

#ifndef GAME_CONFIG_HPP
#define GAME_CONFIG_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace Config {
    constexpr int ServerPort = 11211;
    constexpr int ScreenWidth = 1080;
    constexpr int ScreenHeight = 720;
    constexpr float PlayerSpeed = 5.0f;
    constexpr int WindowFramerateLimit = 60;
    extern std::string GameTitle;
    extern sf::Vector2f ButtonSize;
    extern sf::Vector2f SettingsGameButtonSize;
}

#endif // GAME_CONFIG_HPP
