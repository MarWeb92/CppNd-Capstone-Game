#include "controller.h"
#include <iostream>
#include "SDL.h"


void Controller::HandleInput(bool &running, Player &player) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {

        case SDLK_LEFT:
          player.set_dir(Player::Direction::kBackward);
          break;

        case SDLK_RIGHT:
          player.set_dir(Player::Direction::kForward);
          break;

        case SDLK_SPACE:
          player.set_jump(true);
      }
    }
    else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          player.set_dir(Player::Direction::kStop);
          break;
        case SDLK_RIGHT:
          player.set_dir(Player::Direction::kStop);
          break;
      }
    }
  }
}