#include "player.h"

Player::Player(int x, int y): _x(x), _y(y) {}
Player::Player():_x(0), _y(0) {}
Player ::~Player(){}

int Player::get_x(){return _x;}
int Player::get_y(){return _y;}
void Player::set_x(const int x){_x = x;}
void Player::set_y(const int y){_y = y;}