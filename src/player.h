#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : public Object {
public:
  enum class Direction { kStop, kForward, kBackward };
  enum class JumpState { NoJump, UpwardJump, DownwardJump };

  // Constructor and Destructor
  Player(int x, int y, int refLvl, int screenHeight);
  ~Player();

  void Update();

  // getters and setters
  int get_x();
  int get_y();
  void set_x(const int x);
  void set_y(const int y);
  void set_dir(const Direction dir);
  void set_jump(const bool jump);

  bool alive{true};

private:
  Direction _dir{Direction::kStop};
  JumpState _jumpState{JumpState::NoJump};
  bool _jumpTrigger{false};
  bool _jumping{false};
  int _speed{7};
  int _jumpHeight{350};
};

#endif
