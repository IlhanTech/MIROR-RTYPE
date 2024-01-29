/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ScreenMenu
*/

#ifndef R_TYPE_SCREENMENU_CLIENT_HPP
#define R_TYPE_SCREENMENU_CLIENT_HPP

#include "../IScreen.hpp"
#include "../../../../libs/GameEngine/GameEngine.hpp"

class ScreenMenu : public IScreen {
public:
    ScreenMenu(Game& game, GameEngine& engine);
    void Initialize() override;
    void HandleEvents() override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;
    bool IsRunning() const override;

private:
    Game& game;
    GameEngine& gameEngine;
    bool isRunning;
};

#endif /* !R_TYPE_GAME_SCREENMENU_CLIENT_HPP */

