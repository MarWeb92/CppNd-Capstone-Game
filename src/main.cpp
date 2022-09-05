#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{640};
  constexpr int kStartPlayerX{200};
  constexpr int kStartPlayerY{0};
  constexpr int kPlayerWidth{15};
  constexpr int kPlayerHeight{35};
  constexpr int kGroundLvl{100};

  Renderer renderer(kScreenWidth, kScreenHeight);
  Controller controller;
  Game game(kScreenWidth, kScreenHeight, kGroundLvl, kStartPlayerX, kStartPlayerY, kPlayerWidth, kPlayerHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}