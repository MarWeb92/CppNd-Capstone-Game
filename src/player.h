#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : private Object {
public:
  enum class Direction { kStop, kForward, kBackward };

  // Constructor and Destructor
  Player(int x, int y, int screenHeight);
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
  bool _jump{false};
  int _speed{5};
};

#endif
