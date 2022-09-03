#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
  enum class Direction { kStop, kForward, kBackward };

  // Constructor and Destructor
  Player();
  Player(int x, int y);
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
  float _x, _y;
  Direction _dir{Direction::kStop};
  bool _jump{false};
  float _speed{0.1};
};

#endif
