/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entities/Entity.hpp"
#include "Components/Component.hpp"
#include "Components/Button/Button.hpp"
#include "WindowManager/WindowManager.hpp"
#include "ResourcesManager/ResourceManager.hpp"
#include "Entities/Character/CharacterEntity.hpp"
#include "Entities/Character/Player/PlayerEntity.hpp"
#include "Entities/Character/MissileEntity/MissileEntity.hpp"
#include "Entities/Character/Mobs/MobsEntity.hpp"
#include "AudioManager/AudioManager.hpp"
#include "Server/ServerData.hpp"

class GameEngine {
public:
    GameEngine(int port, sf::IpAddress ip, sf::UdpSocket &socket);
    ~GameEngine();

    void Initialize(int ScreenWidth, int ScreenHeight, int WindowFramerateLimit, std::string WindowName);
    void Update();
    WindowManager& getWindowManager();
    void AddEntity(std::unique_ptr<Entity> entity);
    void AddEntity(std::unique_ptr<CharacterEntity> characterEntity);
    void AddEntity(std::unique_ptr<MobsEntity> mobEntity);
    void AddEntity(std::unique_ptr<PlayerEntity> playerEntity);
    void AddEntityInParallax(std::unique_ptr<Entity> entity);
    void AddComponent(const std::string name, const std::string& texturePath, const sf::Vector2f& size);
    void AddButton(const std::string name, const std::string& imagePath, const std::string& hoverImagePath, const std::string& pressSoundPath, const sf::Vector2f& size, const sf::Vector2f& position);
    const std::vector<std::unique_ptr<Component>>& getComponents() const;
    std::vector<std::unique_ptr<Entity>>& getEntities();
    const std::vector<std::unique_ptr<Entity>>& getParallax() const;
    void UpdateButtons(const sf::RenderWindow& window, AudioManager& audioManager);
    Button* getButton(const std::string& buttonName);
    void removeEntity(Entity* entity);
    void removeComponent(Component* component);
    void removeAllComponents();
    AudioManager& getAudioManager();
    ServerData &getServerData();
    int getPlayersSize();
    Entity* getEntity(const std::string& entityName);
    Entity *getEntityByUid(int uid);
    PlayerEntity *getPlayerByUid(int uid);
    bool entityExist(const std::string& entityName);
    void removeComponentByName(const std::string& name);

private:
    ServerData serverData;
    WindowManager windowManager;
    ResourceManager resourceManager;
    AudioManager audioManager;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> parallax;
    std::vector<std::unique_ptr<Component>> components;
};

#endif /* !GAMEENGINE_HPP_ */
