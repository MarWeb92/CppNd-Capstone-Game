#include "player.h"
#include <chrono>

// Constructor, mainly calling the base class constructor
Player::Player(int x, int y, int w, int h, int refLvl, int screenWidth,
               int screenHeight)
    : Object(x, y, w, h, refLvl, screenHeight), _screenWidth(screenWidth) {}

// Destructor
Player ::~Player() {}

// Overriden virtual setter function for x-coordinate of the base class
void Player::set_x(const int x) {
  if (x <= 0) {
    _x = 0;
  } else if (x >= _screenWidth) {
    _x = _screenWidth;
  } else {
    _x = x;
  }
}

// Overriden virtual setter function for y-coordinate of the base class
void Player::set_y(const int y) {
  if (y <= 0) {
    _y = 0;
  } else if (y >= _screenHeight - _refLvl) {
    _y = _screenWidth - _refLvl;
  } else {
    _y = y;
  }
}

// other setters
void Player::set_dir(const Direction dir) { _dir = dir; }
void Player::set_jump(const bool jump) { _jumpTrigger = jump; }

// Update player x and y coordinates, based on movement and jumping
void Player::Update() {
  // X-Coordinate
  switch (_dir) {
  case (Direction::kStop):
    break;
  case (Direction::kForward):
    set_x(_x + _speed);
    break;
  case (Direction::kBackward):
    set_x(_x - _speed);
    break;
  }

  // Y-Coordinate
  if (((_y <= 0) && (_jumpTrigger == true)) || (_jumping)) {
    switch (_jumpState) {
    case (JumpState::NoJump):
      _jumping = true;
      _jumpState = JumpState::UpwardJump;
      break;

    case (JumpState::UpwardJump):
      if (_y < _jumpHeight) {
        set_y(_y + 0.07 * (_jumpHeight - _y) + 3);
        _y > _jumpHeight ? _y = _jumpHeight : _y = _y;
      } else {
        _jumpState = JumpState::DownwardJump;
      }
      break;

    case (JumpState::DownwardJump):
      if (_y > 0) {
        set_y(_y - 0.07 * (_jumpHeight - _y) - 3);
      } else {
        _y = 0;
        _jumping = false;
        _jumpState = JumpState::NoJump;
        break;
      }
    }
  }
}