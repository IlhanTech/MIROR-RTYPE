/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ScreenGame
*/

#include "ScreenGame.hpp"
#include "../../../../libs/GameEngine/Server/commands.hpp"
#include <functional>

ScreenGame::ScreenGame(Game& game, GameEngine& engine) : game(game), gameEngine(engine), isRunning(true)
{

}

void ScreenGame::Initialize()
{
    sf::RenderWindow& win = gameEngine.getWindowManager().getWindow();

    // gameEngine.AddEntity(std::make_unique<PlayerEntity>(PLAYER_SPRITE, 300, 320, 2/*game.getPlayerData().playerUid*/));
    this->setCanSpawn(true);
    this->setWin(false);
    this->setShowPause(false);
    gameEngine.AddEntityInParallax(std::make_unique<Entity>\
    (PARALLAX_STARS, 0, 0, sf::IntRect({0, 0, 0, 0}), sf::Vector2f(Config::ScreenWidth, Config::ScreenHeight)));
    gameEngine.AddEntity(std::make_unique<MobsEntity>(BOSS_SPRITE,
    940, 0, sf::IntRect({1, 0, 65, 132}), true, this->getMobsSize() + 1));
    gameEngine.AddButton("Resume", MENU_BUTTON_PLAY, HOVER_MENU_BUTTON_PLAY, SOUND_CLICK_BUTTON, Config::ButtonSize, sf::Vector2f(480, 250));
    gameEngine.AddButton("Back", MENU_BUTTON_EXIT, HOVER_MENU_BUTTON_EXIT, SOUND_CLICK_BUTTON, Config::ButtonSize, sf::Vector2f(481, 375));
    filter.setSize(sf::Vector2f(Config::ScreenWidth, Config::ScreenHeight));
    filter.setFillColor(sf::Color(0, 0, 0, 150));
}

void ScreenGame::HandleEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameEngine.getAudioManager().PlaySound(SOUND_CLICK_BUTTON, 100, false);
        printf("ScreenGame::HandleEvents() -> Pause\n");
        this->setShowPause(true);
    }
    if (this->getWin()) {
        printf("You win !\n");
    }
}

int ScreenGame::getMobsSize()
{
    int i = 0;

    for (auto& entity : gameEngine.getEntities())
        if (MobsEntity* mobsEntity = dynamic_cast<MobsEntity*>(entity.get()))
            i++;
    return (i);
}

void ScreenGame::setMobData()
{
    int i = 0;
    for (const auto& entityPtr : gameEngine.getEntities()) {
        if (MobsEntity* mobsEntity = dynamic_cast<MobsEntity*>(entityPtr.get())) {
            sf::Sprite mobSprite = entityPtr->getSprite();
            int mobId = mobsEntity->getMobId();
            int healthPoints = entityPtr->getHealthPoint();

            mobData data;
            data.sprite = mobSprite;
            data.id = mobId;
            data.healthPoints = healthPoints;

            mobsDatas.push_back(data);
        }
    }
}

void ScreenGame::clearMobSprites()
{
    mobsDatas.clear();
}

void ScreenGame::mobsEntitySpawn()
{
    sf::RenderWindow& win = gameEngine.getWindowManager().getWindow();

    for (auto& entity : gameEngine.getEntities()) {
        if (MobsEntity* mobsEntity = dynamic_cast<MobsEntity*>(entity.get())) {
            if (this->getCanSpawn()) {
                std::unique_ptr<MobsEntity> newMobEntity = std::make_unique<MobsEntity>(MOBS1_SPRITE
                , win.getSize().x / 1.2, gameEngine.getEntity(BOSS_SPRITE)->getPos().y + 100,  sf::IntRect({5, 0, 21, 24}), false, this->getMobsSize() + 1);
                gameEngine.AddEntity(std::move(newMobEntity));
                this->setCanSpawn(false);
            }
        }
    }
    clockMobsSpawning();
}

void ScreenGame::updateMobData()
{
    for (auto it = gameEngine.getEntities().begin(); it != gameEngine.getEntities().end();) {
        auto& entity = *it;

        if (MobsEntity* mobsEntity = dynamic_cast<MobsEntity*>(entity.get())) {
            for (auto& mob : mobsDatas) {
                if (mobsEntity->getMobId() == mob.id) {
                    entity->setHealthPoint(mob.healthPoints);
                    if (entity->getHealthPoint() <= 0) {
                        it = gameEngine.getEntities().erase(it);
                        break;
                    }
                }
            }
        }

        if (it != gameEngine.getEntities().end()) {
            ++it;
        }
    }
}

void ScreenGame::Update()
{
    Button *resume = gameEngine.getButton("Resume");
    Button *back = gameEngine.getButton("Back");

    if (this->getShowPause()) {
        gameEngine.UpdateButtons(gameEngine.getWindowManager().getWindow(), gameEngine.getAudioManager());
        if (resume->isClicked(gameEngine.getWindowManager().getWindow())) {
            this->setShowPause(false);
        }
        if (back->isClicked(gameEngine.getWindowManager().getWindow())) {
            printf("ScreenMenu::HandleEvents() -> Exit\n");
            gameEngine.getWindowManager().getWindow().close();
            isRunning = false;
        }
    }

    for (const auto& entity : gameEngine.getEntities()) {
        if (entity) {
            entity->Update(gameEngine.getWindowManager().getWindow()
            , gameEngine.getServerData());
        }
    }
    gameEngine.getAudioManager().Update();
    gameEngine.getAudioManager().ClearSounds();
}

void ScreenGame::move_parallax(const std::unique_ptr<Entity>& entity, int i)
{
    sf::IntRect rect = entity->getSprite().getTextureRect();
    rect.left = rect.left + i;

    entity->setSpriteRect(rect);
}

void ScreenGame::clock_parallax(const std::unique_ptr<Entity>& entity, int i)
{
    seconds = time.asMicroseconds() / 10000.0;
    time = clock.getElapsedTime();

    if (seconds > 2.25) {
        move_parallax(entity, i);
        clock.restart();
    }
}

void ScreenGame::clockMobsSpawning()
{
    seconds_spawn_clock = time_spawn_clock.asSeconds();
    time_spawn_clock = clock_spawn.getElapsedTime();

    if (seconds_spawn_clock > 3) {
        if (gameEngine.entityExist(BOSS_SPRITE)) {
            this->setCanSpawn(true);
        } else {
            this->setCanSpawn(false);
            this->setWin(true);
        }
        clock_spawn.restart();
    }
}

void ScreenGame::Render(sf::RenderWindow& window)
{
    this->setMobData();
    // Render parallax
    int p_i = 0;
    for (const auto& p : gameEngine.getParallax()) {
        if (p) {
            p_i += 1;
            p->Render(gameEngine.getWindowManager().getWindow(), mobsDatas
            , gameEngine.getServerData());
            clock_parallax(p, p_i);
        }
    }
    // Render entities
    for (auto it = gameEngine.getEntities().begin(); it != gameEngine.getEntities().end();) {
        auto& entity = *it;
        entity->Render(window, mobsDatas, gameEngine.getServerData());
        if (entity->getSprite().getPosition().x > window.getSize().x + 5
        || entity->getSprite().getPosition().x < -5) {
            it = gameEngine.getEntities().erase(it);
        } else {
            ++it;
        }
    }
    this->updateMobData();
    this->clearMobSprites();
    this->mobsEntitySpawn();
    // Render components
    if (this->getShowPause()) {
        window.draw(filter);
        for (const auto& component : gameEngine.getComponents()) {
            if (component) {
                component->Render(gameEngine.getWindowManager().getWindow());
            }
        }
    }
}

bool ScreenGame::IsRunning() const
{
    return isRunning;
}
