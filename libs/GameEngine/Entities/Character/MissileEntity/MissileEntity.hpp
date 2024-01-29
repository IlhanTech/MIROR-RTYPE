/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** MissileEntity
*/

#ifndef MISSILEENTITY_HPP_
#define MISSILEENTITY_HPP_

#include "../CharacterEntity.hpp"

class MissileEntity : public CharacterEntity {
public:
    enum DIRECTION {
        WEST,
        EAST,
        NORTH,
        SOUTH
    };

    MissileEntity();
    MissileEntity(float x, float y, DIRECTION direction, int id, int playerUid);
    ~MissileEntity();
    sf::Vector2f getSpritePosition();
    void check_colliding(std::vector<mobData>& mobsDatas);
    bool isColliding(sf::Sprite c_sprite);
    void setReachTarget(bool b);
    bool hasReachedTarget();
    virtual void Update(sf::RenderWindow& window, ServerData &serverData) override;
    virtual void Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
    , ServerData &serverData) override;
    virtual int getId() override;
    int getPlayerUid();

protected:
    DIRECTION direction;
    sf::Clock clock;
    float seconds;
    sf::Time time;
    int id;
    int missileDamage;
    bool targetReached;
    int playerUid;
};

#endif /* !MISSILEENTITY_HPP_ */

