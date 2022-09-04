#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{128};
  constexpr std::size_t kGridHeight{64};
  constexpr float kStartPlayerX{200};
  constexpr float kStartPlayerY{110};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kScreenHeight,kGridWidth, kGridHeight, kStartPlayerX, kStartPlayerY);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}