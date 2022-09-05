#include "player.h"
#include <chrono>

Player::Player(int x, int y, int refLvl, int screenWidth, int screenHeight)
    : Object(x, y, refLvl, screenHeight), _screenWidth(screenWidth) {}
Player ::~Player() {}

int Player::get_x() { return _x; }
int Player::get_y() { return _y; }

void Player::set_x(const int x) {
  if (x <= 0) {
    _x = 0;
  } else if (x >= _screenWidth) {
    _x = _screenWidth;
  } else {
    _x = x;
  }
}
void Player::set_y(const int y) {
    if (y <= 0) {
    _y = 0;
  } else if (y >= _screenHeight - _refLvl) {
    _y = _screenWidth - _refLvl;
  } else {
    _y = y;
  }
}

void Player::set_dir(const Direction dir) { _dir = dir; }
void Player::set_jump(const bool jump) { _jumpTrigger = jump; }

void Player::Update() {
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

  if (((_y <= 0) && (_jumpTrigger == true)) || (_jumping)) {
    // Reset jump trigger
    switch (_jumpState) {
    case (JumpState::NoJump):
      _jumping = true;
      _jumpState = JumpState::UpwardJump;
      break;

    case (JumpState::UpwardJump):
      if (_y < _jumpHeight) {
        set_y(_y + 0.10 * (_jumpHeight - _y) + 5);
        _y > _jumpHeight ? _y = _jumpHeight : _y = _y;
      } else {
        _jumpState = JumpState::DownwardJump;
      }
      break;

    case (JumpState::DownwardJump):
      if (_y > 0) {
        set_y(_y - 0.10 * (_jumpHeight - _y) - 5);
      } else {
        _y = 0;
        _jumping = false;
        _jumpState = JumpState::NoJump;
        break;
      }
    }
  }
}