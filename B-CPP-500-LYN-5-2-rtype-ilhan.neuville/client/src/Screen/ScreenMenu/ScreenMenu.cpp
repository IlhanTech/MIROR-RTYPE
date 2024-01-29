/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ScreenMenu
*/

#include "ScreenMenu.hpp"
#include "../../../../libs/GameEngine/mobData.hpp"
#include <functional>

ScreenMenu::ScreenMenu(Game& game, GameEngine& engine) : game(game), gameEngine(engine), isRunning(true)
{

}

void ScreenMenu::Initialize()
{
    gameEngine.AddComponent("BackgroundMenu", MENU_BACKGROUND, sf::Vector2f(Config::ScreenWidth, Config::ScreenHeight));
    gameEngine.AddButton("Play", MENU_BUTTON_PLAY, HOVER_MENU_BUTTON_PLAY, SOUND_CLICK_BUTTON, Config::ButtonSize, sf::Vector2f(480, 250));
    gameEngine.AddButton("Exit", MENU_BUTTON_EXIT, HOVER_MENU_BUTTON_EXIT, SOUND_CLICK_BUTTON, Config::ButtonSize, sf::Vector2f(481, 375));
    gameEngine.getAudioManager().PlaySound(SOUND_BACKGROUND, 10, true);
}

void ScreenMenu::HandleEvents()
{

}

void ScreenMenu::Update()
{
    gameEngine.UpdateButtons(gameEngine.getWindowManager().getWindow(), gameEngine.getAudioManager());
    Button *play = gameEngine.getButton("Play");
    Button *exit = gameEngine.getButton("Exit");

    if (play->isClicked(gameEngine.getWindowManager().getWindow())) {
        commands cmd;
        std::string payloadPlay = "3 " + std::to_string(game.getPlayerData().playerUid);
        std::string payloadGetAllPlayers = "6 " + std::to_string(game.getPlayerData().playerUid);
        cmd.sendCommand(const_cast<char *>(payloadPlay.c_str()), gameEngine.getServerData());
        cmd.sendCommand(const_cast<char *>(payloadGetAllPlayers.c_str()), gameEngine.getServerData());
        if (game.getPlayerData().isPlaying) {
            gameEngine.getAudioManager().PlaySound(SOUND_START_GAME, 100, false);
            gameEngine.removeAllComponents();
            game.ScreenGameInit();
            game.ScreenChange(ScreenType::GAME);
        }
    }
    if (exit->isClicked(gameEngine.getWindowManager().getWindow())) {
        printf("ScreenMenu::HandleEvents() -> Exit\n");
        gameEngine.getWindowManager().getWindow().close();
        isRunning = false;
    }
}

void ScreenMenu::Render(sf::RenderWindow& window)
{
    std::vector<mobData> nullMob;
    for (const auto& entity : gameEngine.getEntities()) {
        if (entity) {
            entity->Render(gameEngine.getWindowManager().getWindow(), nullMob
            , gameEngine.getServerData());
        }
    }
    for (const auto& component : gameEngine.getComponents()) {
        if (component) {
            component->Render(gameEngine.getWindowManager().getWindow());
        }
    }
}

bool ScreenMenu::IsRunning() const
{
    return isRunning;
}
