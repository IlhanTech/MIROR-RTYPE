/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** AudioManager
*/

#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include <string>
#include <filesystem>

class AudioManager {
public:
    AudioManager();
    void PlaySound(const std::string& soundPath, float volume = 100, bool loop = false);
    void Update();
    void ClearSounds();
    std::string formatPath(const std::string& path);

private:
    struct SoundItem {
        sf::Sound sound;
        bool shouldDestroy;
    };

    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::list<SoundItem> sounds;
    std::string path;
    std::string formattedPath_;
    std::string basePath_ = "assets";
};

#endif // AUDIOMANAGER_HPP
