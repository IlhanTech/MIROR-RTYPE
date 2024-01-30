/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-ilhan.neuville
** File description:
** Game
*/

#ifndef R_TYPE_GAME_CLIENT_HPP
  #define R_TYPE_GAME_CLIENT_HPP

  #include "GameConfig.hpp"
  #include "../include/r_type_client.hpp"
  #include "../../libs/GameEngine/GameEngine.hpp"
  #include "Commands/Commands.hpp"
  #include "../../libs/GameEngine/Server/commands.hpp"
  #include "../src/Screen/ScreenGame/ScreenGame.hpp"
  #include "../src/Screen/ScreenMenu/ScreenMenu.hpp"
  #include "../src/Screen/ScreenWin/ScreenWin.hpp"

  class ScreenGame;
  class ScreenMenu;
  class ScreenWin;

  enum class ScreenType {
      MENU,
      GAME,
      WIN
  };

  class Game {
      public:
          struct playerData {
              int playerUid;
              // pos
              int x;
              int y;
              // make a structure for sprite : sf rect etc
              // store sprite path only to communicate with server
              sf::Sprite sprite; // const &std::string path instead
              // further informations ; to be completed
              bool isConnected;
              bool isPlaying;
          };
          Game(int port, sf::IpAddress ip, sf::UdpSocket &socket);
          void Initialize();
          void HandleEvents();
          void Update();
          void Render();
          bool IsRunning();
          void ShowMenuScreen();
          void ShowGameScreen();
          void ShowWinScreen();
          void ScreenGameInit();
          void ScreenWinInit();
          void ScreenChange(ScreenType screenType);
          void setPlayerData(playerData pData);
          playerData getPlayerData();
          GameEngine& getGameEngine();

          //std::map<int, int*(*)(const char *, Game)> command_map;
          std::map<int, std::function<int(const char*, Game)>> command_map;
  private:
      bool isRunning;
      GameEngine gameEngine;
      playerData pData;
      IScreen* currentScreen;
      std::unique_ptr<ScreenMenu> screenMenu;
      std::unique_ptr<ScreenGame> screenGame;
      std::unique_ptr<ScreenWin> screenWin;
  };

#endif /* !R_TYPE_GAME_ENGINE_CLIENT_HPP */
