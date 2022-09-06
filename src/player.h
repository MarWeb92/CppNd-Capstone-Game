#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

// class Player, publicly inheriting from Object
class Player : public Object {
public:
  enum class Direction { kStop, kForward, kBackward };
  enum class JumpState { NoJump, UpwardJump, DownwardJump };

  // Constructor and Destructor
  Player(int x, int y, int w, int h, int refLvl, int screenWidth,
         int screenHeight);
  ~Player();

  // Update method to update player instance attributes
  void Update();

  // getters and setters
  void set_x(const int x) override;
  void set_y(const int y) override;
  void set_dir(const Direction dir);
  void set_jump(const bool jump);

  // Player state, indicating if game is still running or lost
  bool alive{true};

private:
  Direction _dir{Direction::kStop};        // moving direction of player
  JumpState _jumpState{JumpState::NoJump}; // jump state
  bool _jumpTrigger{false};                // player shall jump
  bool _jumping{false};                    // player is currently jumping
  int _speed{7};                           // player moving speed
  int _jumpHeight{350};                    // height the player can jump
  int _screenWidth; // screenwith for limiting player movement
};

#endif
