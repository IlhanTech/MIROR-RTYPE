#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../Component.hpp"
#include "../../AudioManager/AudioManager.hpp"

class Button : public Component {
public:
    Button(const std::string name, const std::string& imagePath, const std::string& imageHoverPath, const std::string& pressSoundPath, const sf::Vector2f& size, const sf::Vector2f& position);

    void setPosition(const sf::Vector2f& position);
    bool isClicked(const sf::RenderWindow& window) const;
    bool isHovered(const sf::RenderWindow& window) const;
    void UpdateState(const sf::RenderWindow& window, AudioManager& audioManager);
    void UpdateTexture(const std::string& normalImagePath, const std::string& hoverImagePath);

private:
    bool clicked;
    bool hovered;
    std::string name;
    std::string imagePath;
    std::string hoverImagePath;
    std::string pressSoundPath;
};

#endif // BUTTON_HPP
