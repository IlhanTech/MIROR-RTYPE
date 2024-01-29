;/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** MobEntity
*/

#ifndef R_TYPE_MOBS_ENTITY_HPP
    #define R_TYPE_MOBS_ENTITY_HPP

    #include "../CharacterEntity.hpp"

    class MobsEntity : public CharacterEntity {
        public:
            MobsEntity();
            MobsEntity(const std::string& path, float x, float y, sf::IntRect rect
            , bool boss, int id, int playerUid);
            virtual ~MobsEntity();
            void clocktime();
            virtual void Update(sf::RenderWindow& window, ServerData &serverData) override;
            virtual void Render(sf::RenderWindow& window, std::vector<mobData>& mobsDatas
            , ServerData &serverData) override;
            virtual int getId() override;
            int getPlayerConnectionUid();

        private:
            int id;
            bool boss;
            int verticalDirection;
            int playerConnectionUid;
    };

#endif /* !R_TYPE_MOBS_ENTITY_HPP */