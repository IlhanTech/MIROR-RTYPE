/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ScreenGame
*/

#ifndef R_TYPE_SREENGAME_CLIENT_HPP
#define R_TYPE_SREENGAME_CLIENT_HPP

#include "../IScreen.hpp"
#include "../../../../libs/GameEngine/GameEngine.hpp"
#include "../../../../libs/GameEngine/mobData.hpp"
#include "../../../../libs/GameEngine/Entities/Character/Mobs/MobsEntity.hpp"

class ScreenGame : public IScreen {
public:
    ScreenGame(Game& game, GameEngine& engine);
    void Initialize() override;
    void HandleEvents() override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;
    bool IsRunning() const override;
    void clock_parallax(const std::unique_ptr<Entity>& entity, int i);
    void move_parallax(const std::unique_ptr<Entity>& entity, int i);
    void setMobData();
    int getMobsSize();
    int getMissilesSize();
    void updateMobData();
    void clearMobSprites();
    void mobsEntitySpawn();
    void setCanSpawn(bool canSpawn) { this->canSpawn = canSpawn; }
    bool getCanSpawn() { return (this->canSpawn); };
    void setWin(bool win) { this->win = win; }
    bool getWin() { return (this->win); };
    void setShowPause(bool showPause) { this->showPause = showPause; }
    bool getShowPause() { return (this->showPause); };
    void clockMobsSpawning();

private:
    Game& game;
    GameEngine& gameEngine;
    std::vector<mobData> mobsDatas;
    bool isRunning;
    sf::Clock clock;
    float seconds;
    sf::Time time;
    bool canSpawn;
    sf::Clock clock_spawn;
    sf::Time time_spawn_clock;
    float seconds_spawn_clock;
    bool win;
    sf::RectangleShape filter;
    bool showPause;
};

#endif /* !R_TYPE_GAME_SCREENGAME_CLIENT_HPP */

