/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville [WSL: Ubuntu]
** File description:
** gameStateData
*/

#ifndef GAMESTATEDATA_HPP_
#define GAMESTATEDATA_HPP_

struct gameStateData {
    bool isConnected;
    bool isPlaying;
    bool isDead;
    bool hasWon;
    bool hasLost;
    int playerNumber;
};

#endif /* !GAMESTATEDATA_HPP_ */
