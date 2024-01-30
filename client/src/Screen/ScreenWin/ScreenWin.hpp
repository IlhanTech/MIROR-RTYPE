/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ScreenWin
*/

#ifndef R_TYPE_SREENWIN_CLIENT_HPP
#define R_TYPE_SREENWIN_CLIENT_HPP

#include "../IScreen.hpp"
#include "../../../../libs/GameEngine/GameEngine.hpp"
#include "../../../../libs/GameEngine/mobData.hpp"
#include "../../../../libs/GameEngine/Entities/Character/Mobs/MobsEntity.hpp"

class ScreenWin : public IScreen {
public:
    ScreenWin(Game& game, GameEngine& engine);
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

#endif /* !R_TYPE_GAME_SCREENWIN_CLIENT_HPP */

