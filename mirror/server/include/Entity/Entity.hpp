/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    #include "../DataStruct/connectionData.hpp"
    #include "../DataStruct/gameplayData.hpp"
    #include "../DataStruct/gameStateData.hpp"

    class Entity
    {
        public:
            Entity();
            virtual ~Entity();
            virtual void setGameplayData(gameplayData datas);
            virtual gameplayData getGameplayData();

            int getHealthPoints();
            void setHealthPoints(int health);
            pos getPosition();
            void setPosition(pos position);
            virtual int getUid();
            void setUid(int uid);
        private:
            gameplayData gPlayData;

            int health;
            pos position;
            int uid;
    };

#endif /* !ENTITY_HPP_ */
