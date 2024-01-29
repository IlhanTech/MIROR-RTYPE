/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** CharacterEntity
*/

#ifndef R_TYPE_CHARACTER_ENTITY_HPP
#define R_TYPE_CHARACTER_ENTITY_HPP

#include "../Entity.hpp"
#include "../../AudioManager/AudioManager.hpp"

class CharacterEntity : public Entity {
public:
    CharacterEntity();
    CharacterEntity(const std::string& path, float x, float y, int playerNumber);
    virtual ~CharacterEntity();

    virtual void Update(sf::RenderWindow& window, ServerData &serverData) override;
    virtual void Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
    , ServerData &serverData) override;
    sf::Sprite getSprite();
    void clocktime();
protected:
    sf::Clock clock;
    float seconds;
    sf::Time time;
    AudioManager audioManager;
};

#endif /* !R_TYPE_CHARACTER_ENTITY_HPP */