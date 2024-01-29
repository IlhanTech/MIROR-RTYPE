/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Component
*/

#ifndef Component_HPP
#define Component_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
#include <iostream>

class Component {
public:
    Component(const std::string name, const std::string& imagePath, const sf::Vector2f& size);
    virtual ~Component();

    void Update();
    void Render(sf::RenderWindow& window);
    static std::string formatPath(const std::string& path);

    std::string getName() const;

protected:
    sf::Texture texture;
    sf::Sprite sprite;

private:
    std::string name;
    std::string path;
    std::string formattedPath_;
    std::string basePath_ = "assets";
};

#endif // Component_HPP
