/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** AudioManager
*/

#include "AudioManager.hpp"

AudioManager::AudioManager()
{

}

std::string AudioManager::formatPath(const std::string& path)
{
    std::filesystem::path currentPath = std::filesystem::current_path();

    if (currentPath.string().find("client") != std::string::npos) {
        currentPath = currentPath.parent_path();
    }

    std::filesystem::path fullPath = currentPath / path;
    return fullPath.string();
}

void AudioManager::PlaySound(const std::string& soundPath, float volume, bool loop)
{
    if (soundBuffers.find(formatPath(soundPath)) == soundBuffers.end()) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(formatPath(soundPath))) {
            return;
        }
        soundBuffers[soundPath] = buffer;
    }

    sounds.emplace_back();
    SoundItem& soundItem = sounds.back();
    soundItem.sound.setBuffer(soundBuffers[soundPath]);
    soundItem.sound.setLoop(loop);
    soundItem.sound.setVolume(volume);
    soundItem.shouldDestroy = !loop;
    soundItem.sound.play();
}

void AudioManager::Update()
{
    for (auto it = sounds.begin(); it != sounds.end();) {
        if (it->shouldDestroy && it->sound.getStatus() == sf::Sound::Stopped) {
            it = sounds.erase(it);
        } else {
            ++it;
        }
    }
}

void AudioManager::ClearSounds()
{
    sounds.clear();
}