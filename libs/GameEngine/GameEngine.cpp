/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** GameEngine
*/

#include "GameEngine.hpp"
#include <iostream>
#include <filesystem>
#include <memory>

GameEngine::GameEngine(int port, sf::IpAddress ip, sf::UdpSocket &socket)
: windowManager(), resourceManager(), serverData(port, ip, socket) {}

void GameEngine::Initialize(int ScreenWidth, int ScreenHeight, int WindowFramerateLimit, std::string WindowName)
{
    windowManager.create(ScreenWidth, ScreenHeight, WindowFramerateLimit, WindowName);
}

GameEngine::~GameEngine()
{
    windowManager.close();
}

void GameEngine::Update()
{

}

WindowManager& GameEngine::getWindowManager()
{
    return windowManager;
}

void GameEngine::AddEntityInParallax(std::unique_ptr<Entity> entity)
{
    parallax.push_back(std::move(entity));
}

void GameEngine::AddMob(std::unique_ptr<MobsEntity> mobEntity)
{
    this->mobsEntities.push_back(std::move(mobEntity));
}

void GameEngine::AddPlayer(std::unique_ptr<PlayerEntity> playerEntity)
{
    playerEntities.push_back(std::move(playerEntity));
}

void GameEngine::AddMissile(std::unique_ptr<MissileEntity> missileEntity)
{
    this->missileEntities.push_back(std::move(missileEntity));
}

void GameEngine::AddComponent(const std::string name, const std::string& texturePath, const sf::Vector2f& size)
{
    components.push_back(std::make_unique<Component>(name, texturePath, size));
}

void GameEngine::AddButton(const std::string name, const std::string& imagePath, const std::string& hoverImagePath, const std::string& pressSoundPath, const sf::Vector2f& size, const sf::Vector2f& position)
{
    components.push_back(std::make_unique<Button>(name, imagePath, hoverImagePath, pressSoundPath, size, position));
}

const std::vector<std::unique_ptr<Entity>>& GameEngine::getParallax() const
{
    return parallax;
}

std::vector<std::unique_ptr<PlayerEntity>>& GameEngine::getPlayerEntities()
{
    return (this->playerEntities);
}

std::vector<std::unique_ptr<MissileEntity>>& GameEngine::getMissileEntities()
{
    return (this->missileEntities);
}

std::vector<std::unique_ptr<MobsEntity>>& GameEngine::getMobEntities()
{
    return (this->mobsEntities);
}

PlayerEntity *GameEngine::getPlayerByUid(int uid)
{
    for (auto& player : this->playerEntities) {
        if (player->getUid() == uid)
            return (player).get();
    }
    return (nullptr);
}

MissileEntity *GameEngine::getMissileById(int id)
{
    for (auto& missile : this->missileEntities) {
        if (missile->getId() == id)
            return (missile.get());
    }
    return (nullptr);
}

MobsEntity *GameEngine::getMobById(int id)
{
    for (auto& mob : this->mobsEntities) {
        if (mob->getId() == id)
            return (mob.get());
    }
    return (nullptr);
}

const std::vector<std::unique_ptr<Component>>& GameEngine::getComponents() const
{
    return components;
}

void GameEngine::UpdateButtons(const sf::RenderWindow& window, AudioManager& audioManager)
{
    for (auto& component : components) {
        Button* button = dynamic_cast<Button*>(component.get());
        if (button != nullptr) {
            button->UpdateState(window, audioManager);
        }
    }
}

Button* GameEngine::getButton(const std::string& buttonName)
{
    for (const auto& component : getComponents()) {
        if (component->getName() == buttonName) {
            return dynamic_cast<Button*>(component.get());
        }
    }
    throw std::runtime_error("Button not found: " + buttonName);
}

void GameEngine::removePlayer(PlayerEntity* entity)
{
    auto it = std::find_if(playerEntities.begin(), playerEntities.end()
    , [entity](const std::unique_ptr<PlayerEntity>& e) {
        return e.get() == entity;
    });
    if (it != playerEntities.end()) {
        playerEntities.erase(it);
    }
}

void GameEngine::removeMissile(MissileEntity* entity)
{
    auto it = std::find_if(missileEntities.begin(), missileEntities.end()
    , [entity](const std::unique_ptr<MissileEntity>& e) {
        return e.get() == entity;
    });
    if (it != missileEntities.end()) {
        missileEntities.erase(it);
    }
}

void GameEngine::removeMob(MobsEntity* entity)
{
    auto it = std::find_if(mobsEntities.begin(), mobsEntities.end()
    , [entity](const std::unique_ptr<MobsEntity>& e) {
        return e.get() == entity;
    });
    if (it != mobsEntities.end()) {
        mobsEntities.erase(it);
    }
}

void GameEngine::removeComponent(Component* component)
{
    auto it = std::find_if(components.begin(), components.end(), [component](const std::unique_ptr<Component>& c) {
        return c.get() == component;
    });
    if (it != components.end()) {
        components.erase(it);
    }
}

void GameEngine::removeComponentByName(const std::string& name)
{
    auto it = std::find_if(components.begin(), components.end(), [&name](const std::unique_ptr<Component>& c) {
        return c->getName() == name;
    });
    if (it != components.end()) {
        components.erase(it);
    }
}

void GameEngine::removeAllComponents()
{
    components.clear();
}

AudioManager& GameEngine::getAudioManager()
{
    return audioManager;
}

ServerData &GameEngine::getServerData()
{
    return (this->serverData);
}

int GameEngine::getPlayersSize()
{
    int playersSize = 0;

    for (auto& entity : this->playerEntities)
            ++playersSize;
    return (playersSize);
}

int GameEngine::getMissilesSize()
{
    int missilesSize = 0;

    for (auto& entity : this->missileEntities)
            ++missilesSize;
    return (missilesSize);
}

int GameEngine::getMobsSize()
{
    int mobsSize = 0;

    for (auto& entity : this->mobsEntities)
            ++mobsSize;
    return (mobsSize);
}

MobsEntity* GameEngine::getMobEntity(const std::string& entityName)
{
    for (const auto& entity : getMobEntities()) {
        if (entity->getName() == entityName) {
            return (entity.get());
        }
    }
    throw std::runtime_error("Entity not found: " + entityName);
}

bool GameEngine::mobEntityExist(const std::string& entityName)
{
    for (const auto& entity : this->getMobEntities()) {
        if (entity->getName() == entityName) {
            return (true);
        }
    }
    return (false);
}

