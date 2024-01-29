/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Entity
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
#include <iostream>

#include "../mobData.hpp"
#include "../Server/ServerData.hpp"

class Entity {
public:

    struct pos {
        float x;
        float y;
    };

    Entity();
    Entity(const std::string& imagePath, float posX = 0, float posY = 0);
    Entity(const std::string& imagePath, float posX, float posY, sf::IntRect rect, const sf::Vector2f& size);
    ~Entity();

    virtual void Update(sf::RenderWindow& window, ServerData &serverData);
    virtual void Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
    , ServerData &serverData);
    virtual sf::Sprite getSprite();
    virtual void setSpriteRect(sf::IntRect rect);
    static std::string formatPath(const std::string& path);
    void setHealthPoint(int healthPoints);
    int getHealthPoint();
    std::string getName() const;
    pos getPos() const;
    void setPos(pos position);

protected:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string path;
    std::string formattedPath_;
    std::string basePath_ = "assets";
    int healthPoints;
    pos position;
};

#endif // ENTITY_HPP
