#include "player.h"

Player::Player(float x, float y): _x(x), _y(y) {}
Player::Player():_x(0), _y(0) {}
Player ::~Player(){}

float Player::get_x(){return _x;}
float Player::get_y(){return _y;}
void Player::set_x(const float x){_x = x;}
void Player::set_y(const float y){_y = y;}
void Player::set_dir(const Direction dir){_dir = dir;}
void Player::set_jump(const bool jump){_jump = jump;}

void Player::Update(){
    switch (_dir){
        case(Direction::kStop):
            break;
        case(Direction::kForward):
            set_x(_x + _speed);
            break;
        case(Direction::kBackward):
            set_x(_x - _speed);
            break;

    }

}