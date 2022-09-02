#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
Player();
Player(int x, int y);
~Player();
int get_x();
int get_y();
void set_x(const int x);
void set_y(const int y);

private:
  int _x, _y;
};

#endif
