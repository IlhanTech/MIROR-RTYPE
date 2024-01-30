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
    gameEngine.AddMob(std::make_unique<MobsEntity>(BOSS_SPRITE,
    940, 0, sf::IntRect({1, 0, 65, 132}), true, this->getMobsSize() + 1
    , game.getPlayerData().playerUid));
    // commands cmds;
    // cmds.sendCommand(const_cast<char *>(std::string("4 "
    // + std::to_string(game.getPlayerData().playerUid) + " entityType:MobBoss"
    // + " positionX:" + std::to_string(940)
    // + " positionY:" + std::to_string(0)).c_str()), gameEngine.getServerData());
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

    for (auto& entity : gameEngine.getMobEntities())
        i++;
    return (i);
}

int ScreenGame::getMissilesSize()
{
    int i = 0;

    for (auto& entity : gameEngine.getMissileEntities())
        i++;
    return (i);
}

void ScreenGame::setMobData()
{
    int i = 0;
    for (const auto& mob : gameEngine.getMobEntities()) {
        sf::Sprite mobSprite = mob->getSprite();
        int mobId = mob->getId();
        int healthPoints = mob->getHealthPoint();

        mobData data;
        data.sprite = mobSprite;
        data.id = mobId;
        data.healthPoints = healthPoints;

        mobsDatas.push_back(data);
    }
}

void ScreenGame::clearMobSprites()
{
    mobsDatas.clear();
}

void ScreenGame::mobsEntitySpawn()
{
    sf::RenderWindow& win = gameEngine.getWindowManager().getWindow();

    for (auto& entity : gameEngine.getMobEntities()) {
        if (this->getCanSpawn()) {
            // std::unique_ptr<MobsEntity> newMobEntity = std::make_unique<MobsEntity>(MOBS1_SPRITE
            // , win.getSize().x / 1.2, gameEngine.getMobEntity(BOSS_SPRITE)->getPos().y + 100
            // ,  sf::IntRect({5, 0, 21, 24}), false, this->getMobsSize() + 1
            // , game.getPlayerData().playerUid);
            // gameEngine.AddMob(std::move(newMobEntity));
            commands cmds;
            cmds.sendCommand(const_cast<char *>(std::string("4 "
            + std::to_string(game.getPlayerData().playerUid) + " entityType:Mob"
            + " positionX:" + std::to_string(win.getSize().x / 1.2)
            + " positionY:" + std::to_string(gameEngine.getMobEntity(BOSS_SPRITE)->getPos().y + 100))
            .c_str()), gameEngine.getServerData());
            this->setCanSpawn(false);
        }
    }
    clockMobsSpawning();
}

void ScreenGame::updateMobData()
{
    for (auto it = gameEngine.getMobEntities().begin(); it != gameEngine.getMobEntities().end();) {
        auto& entity = *it;

        if (MobsEntity* mobsEntity = dynamic_cast<MobsEntity*>(entity.get())) {
            for (auto& mob : mobsDatas) {
                if (mobsEntity->getId() == mob.id) {
                    entity->setHealthPoint(mob.healthPoints);
                    if (entity->getHealthPoint() <= 0) {
                        it = gameEngine.getMobEntities().erase(it);
                        break;
                    }
                }
            }
        }

        if (it != gameEngine.getMobEntities().end()) {
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
            //faudrait rajouter une fonction qui envoit au serveur pour la deconnexion du client
            exit(0);
        }
    }

    for (const auto& player : gameEngine.getPlayerEntities())
        if (player)
            player->Update(gameEngine.getWindowManager().getWindow()
            , gameEngine.getServerData());
    for (const auto& mob : gameEngine.getMobEntities())
        if (mob)
            mob->Update(gameEngine.getWindowManager().getWindow()
            , gameEngine.getServerData());
    for (const auto& missile : gameEngine.getMissileEntities())
        if (missile)
            missile->Update(gameEngine.getWindowManager().getWindow()
            , gameEngine.getServerData());
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
        if (gameEngine.mobEntityExist(BOSS_SPRITE)) {
            this->setCanSpawn(true);
        } else {
            this->setCanSpawn(false);
            this->setWin(true);
            //gameEngine.removeAllComponents();
            game.ScreenWinInit();
            game.ScreenChange(ScreenType::WIN);
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
    for (auto it = gameEngine.getMobEntities().begin(); it != gameEngine.getMobEntities().end();) {
        auto& mob = *it;
        mob->Render(window, mobsDatas, gameEngine.getServerData());
        if (mob->getSprite().getPosition().x > window.getSize().x + 5
        || mob->getSprite().getPosition().x < -5) {
            // commands cmds;
            // cmds.sendCommand(const_cast<char *>(std::string("7 "
            // + std::to_string(game.getPlayerData().playerUid) + " entityType:Mob "
            // + "EntityId:" + std::to_string(entity.get()->getId())).c_str())
            // , gameEngine.getServerData());
            // it = gameEngine.getEntities().erase(it);
            printf("removed mob %d\n", mob.get()->getId());
            game.getGameEngine().removeMob(mob.get());
            printf("ok, removed\n");
        } else {
            ++it;
        }
    }
    for (auto it = gameEngine.getMissileEntities().begin(); it != gameEngine.getMissileEntities().end();) {
        auto& missile = *it;
        missile->Render(window, mobsDatas, gameEngine.getServerData());
        if (missile->getSprite().getPosition().x > window.getSize().x + 5
        || missile->getSprite().getPosition().x < -5) {
            // commands cmds;
            // cmds.sendCommand(const_cast<char *>(std::string("7 "
            // + std::to_string(game.getPlayerData().playerUid) + " entityType:Mob "
            // + "EntityId:" + std::to_string(entity.get()->getId())).c_str())
            // , gameEngine.getServerData());
            // it = gameEngine.getEntities().erase(it);
            printf("removed missile %d\n", missile.get()->getId());
            game.getGameEngine().removeMissile(missile.get());
            printf("ok, removed\n");
        } else {
            ++it;
        }
    }
    for (auto it = gameEngine.getPlayerEntities().begin(); it != gameEngine.getPlayerEntities().end();) {
        auto& player = *it;
        player->Render(window, mobsDatas, gameEngine.getServerData());
        if (player->getSprite().getPosition().x > window.getSize().x + 5
        || player->getSprite().getPosition().x < -5) {
            // commands cmds;
            // cmds.sendCommand(const_cast<char *>(std::string("7 "
            // + std::to_string(game.getPlayerData().playerUid) + " entityType:Mob "
            // + "EntityId:" + std::to_string(entity.get()->getId())).c_str())
            // , gameEngine.getServerData());
            // it = gameEngine.getEntities().erase(it);
            printf("removed player %d\n", player.get()->getId());
            game.getGameEngine().removePlayer(player.get());
            printf("ok, removed\n");
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
