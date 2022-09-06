#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

class Controller {
public:
  void HandleInput(bool &running, Player &player);

private:
  void ChangeDirection(Player::Direction input, Player &player);

  bool _keyRightPressed{false};
  bool _keyLeftPressed{false};
  bool _keySpacePressed{false};
};

#endif