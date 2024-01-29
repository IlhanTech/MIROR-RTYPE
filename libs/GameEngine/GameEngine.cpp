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

void GameEngine::AddEntity(std::unique_ptr<Entity> entity)
{
    entities.push_back(std::move(entity));
}

void GameEngine::AddEntity(std::unique_ptr<CharacterEntity> characterEntity)
{
    entities.push_back(std::move(characterEntity));
}

void GameEngine::AddEntity(std::unique_ptr<MobsEntity> mobEntity)
{
    entities.push_back(std::move(mobEntity));
}

void GameEngine::AddEntity(std::unique_ptr<PlayerEntity> playerEntity)
{
    entities.push_back(std::move(playerEntity));
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

std::vector<std::unique_ptr<Entity>>& GameEngine::getEntities()
{
    return entities;
}

PlayerEntity *GameEngine::getPlayerByUid(int uid)
{
    PlayerEntity *player = nullptr;

    for (auto& entity : this->entities) {
        if (PlayerEntity *player = dynamic_cast<PlayerEntity *>(entity.get())) {
            if (player->getUid() == uid)
                return (player);
        }
    }
    return (player);
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

void GameEngine::removeEntity(Entity* entity)
{
    auto it = std::find_if(entities.begin(), entities.end(), [entity](const std::unique_ptr<Entity>& e) {
        return e.get() == entity;
    });
    if (it != entities.end()) {
        entities.erase(it);
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

    for (auto& entity : this->entities)
        if (PlayerEntity *player = dynamic_cast<PlayerEntity *>(entity.get()))
            ++playersSize;
    return (playersSize);
}

Entity* GameEngine::getEntity(const std::string& entityName)
{
    for (const auto& entity : getEntities()) {
        if (MobsEntity *mobEntity = dynamic_cast<MobsEntity *>(entity.get())) {
            if (entity->getName() == entityName) {
                return (entity.get());
            }
        }
    }
    throw std::runtime_error("Entity not found: " + entityName);
}

bool GameEngine::entityExist(const std::string& entityName)
{
    for (const auto& entity : getEntities()) {
        if (MobsEntity *mobEntity = dynamic_cast<MobsEntity *>(entity.get())) {
            if (entity->getName() == entityName) {
                return (true);
            }
        }
    }
    return (false);
}

