/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** ScreenGame
*/

#include "ScreenWin.hpp"
#include <functional>

ScreenWin::ScreenWin(Game& game, GameEngine& engine) : game(game), gameEngine(engine), isRunning(true)
{

}

void ScreenWin::Initialize()
{
    sf::RenderWindow& win = gameEngine.getWindowManager().getWindow();

    gameEngine.AddComponent("BackgroundWin", MENU_BACKGROUND_WIN, sf::Vector2f(Config::ScreenWidth, Config::ScreenHeight));
    gameEngine.AddButton("Exit", MENU_BUTTON_EXIT, HOVER_MENU_BUTTON_EXIT, SOUND_CLICK_BUTTON, Config::ButtonSize, sf::Vector2f(481, 375));
}

void ScreenWin::HandleEvents()
{

}

void ScreenWin::Update()
{
    Button *back = gameEngine.getButton("Back");

    gameEngine.UpdateButtons(gameEngine.getWindowManager().getWindow(), gameEngine.getAudioManager());
    if (back->isClicked(gameEngine.getWindowManager().getWindow())) {
        printf("ScreenMenu::HandleEvents() -> Exit\n");
        gameEngine.getWindowManager().getWindow().close();
        isRunning = false;
        //faudrait rajouter une fonction qui envoit au serveur pour la deconnexion du client
        exit(0);
    }
    gameEngine.getAudioManager().Update();
    gameEngine.getAudioManager().ClearSounds();
}

void ScreenWin::Render(sf::RenderWindow& window)
{
    for (const auto& component : gameEngine.getComponents()) {
        if (component) {
            component->Render(gameEngine.getWindowManager().getWindow());
        }
    }
}

bool ScreenWin::IsRunning() const
{
    return isRunning;
}
