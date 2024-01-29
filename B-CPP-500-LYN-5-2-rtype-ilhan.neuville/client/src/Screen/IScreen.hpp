/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ScreenManager
*/

#include <SFML/Graphics.hpp>
#include "../../../libs/GameEngine/Server/commands.hpp"
#include "../../include/Define.hpp"
#include "../../include/Game.hpp"

#ifndef ISCREEN_HPP
#define ISCREEN_HPP

class IScreen {
public:
    virtual void Initialize() = 0;
    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual bool IsRunning() const = 0;

    virtual ~IScreen() {}
};

#endif // ISCREEN_HPP