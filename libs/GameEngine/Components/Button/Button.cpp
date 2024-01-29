/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(const std::string name, const std::string& imagePath, const std::string& imageHoverPath, const std::string& pressSoundPath, const sf::Vector2f& size, const sf::Vector2f& position)
: Component(name, imagePath, size), clicked(false), hovered(false), name(name), imagePath(imagePath), hoverImagePath(imageHoverPath), pressSoundPath(pressSoundPath)
{
    setPosition(position);
}

void Button::setPosition(const sf::Vector2f& position)
{
    sprite.setPosition(position);
}

bool Button::isClicked(const sf::RenderWindow& window) const
{
    return clicked;
}

bool Button::isHovered(const sf::RenderWindow& window) const
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::UpdateState(const sf::RenderWindow& window, AudioManager& audioManager)
{
    bool previouslyHovered = hovered;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    hovered = sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    if (hovered && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        clicked = true;
        audioManager.PlaySound(pressSoundPath);
    } else {
        clicked = false;
    }

    if (hovered != previouslyHovered) {
        UpdateTexture(imagePath, hoverImagePath);
    }
}

void Button::UpdateTexture(const std::string& normalImagePath, const std::string& hoverImagePath)
{
    sf::Texture newTexture;
    std::string imagePath = hovered ? hoverImagePath : normalImagePath;

    if (newTexture.loadFromFile(Component::formatPath(imagePath))) {
        texture = newTexture;
        sprite.setTexture(texture);
    } else {
        std::cout << "Error: could not load new texture from " << imagePath << std::endl;
    }
}
