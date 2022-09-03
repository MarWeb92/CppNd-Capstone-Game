#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
  enum class Direction { kStop, kForward, kBackward };

  // Constructor and Destructor
  Player();
  Player(const float x, const float y);
  ~Player();

  void Update();

  // getters and setters
  float get_x();
  float get_y();
  void set_x(const float x);
  void set_y(const float y);
  void set_dir(const Direction dir);
  void set_jump(const bool jump);

  bool alive{true};

private:
  float _x, _y;
  Direction _dir{Direction::kStop};
  bool _jump{false};
  float _speed{5.0};
};

#endif
