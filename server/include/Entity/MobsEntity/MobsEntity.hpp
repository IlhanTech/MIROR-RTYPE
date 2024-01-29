/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** MobsEntity
*/

#ifndef MOBSENTITY_HPP_
    #define MOBSENTITY_HPP_

    #include "../Entity.hpp"

    class MobsEntity : public Entity
    {
        public:
            MobsEntity();
            MobsEntity(int id);
            ~MobsEntity();

            virtual int getUid() override;
        private:
            int id;
    };

#endif /* !MOBSENTITY_HPP_ */
