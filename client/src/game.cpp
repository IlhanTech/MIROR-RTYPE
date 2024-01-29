/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** game
*/

#include "../include/Game.hpp"

Game::Game(int port, sf::IpAddress ip, sf::UdpSocket &socket)
: isRunning(true), gameEngine(port, ip, socket) {}

void Game::setPlayerData(playerData pData)
{
    this->pData = pData;
}

Game::playerData Game::getPlayerData()
{
    return (this->pData);
}

GameEngine& Game::getGameEngine()
{
    return (this->gameEngine);
}

void Game::Initialize()
{
    gameEngine.Initialize(Config::ScreenWidth, Config::ScreenHeight, Config::WindowFramerateLimit, Config::GameTitle);
    this->isRunning = true;
    screenMenu = std::make_unique<ScreenMenu>(*this, gameEngine);
    screenGame = std::make_unique<ScreenGame>(*this, gameEngine);
    screenMenu->Initialize();
    ScreenChange(ScreenType::MENU);
    commands cmd;
    cmd.sendCommand(const_cast<char *>(std::string("1 connect").c_str()), gameEngine.getServerData());
}

void Game::ScreenGameInit()
{
    screenGame->Initialize();
}

void Game::ScreenChange(ScreenType screenType)
{
    if (screenType == ScreenType::MENU) {
        ShowMenuScreen();
    } else if (screenType == ScreenType::GAME) {
        ShowGameScreen();
    }
}

void Game::ShowMenuScreen()
{
    currentScreen = screenMenu.get();
}

void Game::ShowGameScreen()
{
    currentScreen = screenGame.get();
}

void Game::HandleEvents()
{
    sf::Event event;
    while (gameEngine.getWindowManager().getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
        }
        if (currentScreen) {
            currentScreen->HandleEvents();
        }
    }
}

void Game::Update()
{
    if (currentScreen) {
        currentScreen->Update();
    }
}

void Game::Render()
{
    gameEngine.getWindowManager().clear();
    if (currentScreen) {
        currentScreen->Render(gameEngine.getWindowManager().getWindow());
    }
    gameEngine.getWindowManager().display();
}

bool Game::IsRunning()
{
    return isRunning;
}
