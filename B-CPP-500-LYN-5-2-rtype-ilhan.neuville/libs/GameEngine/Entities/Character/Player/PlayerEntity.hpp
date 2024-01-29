/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** PlayerEntity
*/

#ifndef R_TYPE_PLAYER_ENTITY_HPP
#define R_TYPE_PLAYER_ENTITY_HPP

#include "../CharacterEntity.hpp"
#include "../MissileEntity/MissileEntity.hpp"

class PlayerEntity : public CharacterEntity {
public:
    PlayerEntity();
    PlayerEntity(const std::string& path, float x, float y, int playerNumber);
    ~PlayerEntity();

    virtual void addMissile(std::unique_ptr<MissileEntity> missileEntity);
    virtual void Update(sf::RenderWindow& window, ServerData &serverData) override;
    virtual void Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
    , ServerData &serverData) override;
    void clock_timer(sf::Vector2f pos);
    void setUid(int uid);
    int getUid();
protected:
    std::vector<std::unique_ptr<MissileEntity>> missiles;
    int uid;
};

#endif /* !R_TYPE_PLAYER_ENTITY_HPP */