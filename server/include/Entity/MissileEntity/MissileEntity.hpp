/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** MissileEntity
*/

#ifndef MISSILEENTITY_HPP_
    #define MISSILEENTITY_HPP_

    #include "../Entity.hpp"

    class MissileEntity : public Entity
    {
        public:
            MissileEntity();
            MissileEntity(int id);
            ~MissileEntity();

            virtual int getUid() override;
        private:
            int id;
    };

#endif /* !MISSILEENTITY_HPP_ */
