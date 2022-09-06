#include "controller.h"
#include "SDL.h"
#include "player.h"

// Handle the change in direction of the player.
// In case of a SDL_KEYUP event, leading to kStop as input, it might be
// that the opposite direction key is still pressed.
void Controller::ChangeDirection(Player::Direction input, Player &player) {

  switch (input) {
  case Player::Direction::kForward:
    player.set_dir(Player::Direction::kForward);
    break;
  case Player::Direction::kBackward:
    player.set_dir(Player::Direction::kBackward);
    break;
  // critical part, check if other key is still pressed
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

// Main input controller.
// React on key press/release events and store the key pressed state.
void Controller::HandleInput(bool &running, Player &player) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    // Close window
    if (e.type == SDL_QUIT) {
      player.alive = false;
      running = false;
    }

    // Key pressed event
    else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {

      // Left arrow key OR 'a' key
      case SDLK_LEFT:
      case SDLK_a:
        _keyLeftPressed = true;
        ChangeDirection(Player::Direction::kBackward, player);
        break;

      // Right arrow key OR 'd' key
      case SDLK_RIGHT:
      case SDLK_d:
        _keyRightPressed = true;
        ChangeDirection(Player::Direction::kForward, player);
        break;

      // Space bar
      case SDLK_SPACE:
        _keySpacePressed = true;
        player.set_jump(true);
      }
    }

    // Key released event
    else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
      // Left arrow key OR 'a' key
      case SDLK_LEFT:
      case SDLK_a:
        _keyLeftPressed = false;
        ChangeDirection(Player::Direction::kStop, player);
        break;
      // Right arrow key OR 'd' key
      case SDLK_RIGHT:
      case SDLK_d:
        _keyRightPressed = false;
        ChangeDirection(Player::Direction::kStop, player);
        break;
      // Space bar
      case SDLK_SPACE:
        _keySpacePressed = false;
        player.set_jump(false);
        break;
      }
    }
  }
}