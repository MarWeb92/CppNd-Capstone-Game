#include "controller.h"
#include "SDL.h"
#include "player.h"
#include <iostream>

void Controller::ChangeDirection(Player::Direction input, Player &player) {

  switch (input) {
  case Player::Direction::kForward:
    player.set_dir(Player::Direction::kForward);
    break;
  case Player::Direction::kBackward:
    player.set_dir(Player::Direction::kBackward);
    break;
  case Player::Direction::kStop:
    if (_keyLeftPressed == true) {
      player.set_dir(Player::Direction::kBackward);
    } else if (_keyRightPressed == true) {
      player.set_dir(Player::Direction::kForward);
    } else {
      player.set_dir(Player::Direction::kStop);
    }
    break;
  }
}

void Controller::HandleInput(bool &running, Player &player) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {

      case SDLK_LEFT:
        _keyLeftPressed = true;
        ChangeDirection(Player::Direction::kBackward, player);
        break;

      case SDLK_RIGHT:
        _keyRightPressed = true;
        ChangeDirection(Player::Direction::kForward, player);
        break;

      case SDLK_SPACE:
        _keySpacePressed = true;
        player.set_jump(true);
      }
    } else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
      case SDLK_LEFT:
        _keyLeftPressed = false;
        ChangeDirection(Player::Direction::kStop, player);
        break;
      case SDLK_RIGHT:
        _keyRightPressed = false;
        ChangeDirection(Player::Direction::kStop, player);
        break;
      case SDLK_SPACE:
        _keySpacePressed = false;
        player.set_jump(false);
        break;
      }
    }
  }
}