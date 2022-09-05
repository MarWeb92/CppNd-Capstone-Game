#include "player.h"

Player::Player(int x, int y, int refLvl, int screenHeight):Object(x, y, refLvl, screenHeight) {}
Player ::~Player(){}

int Player::get_x(){return _x;}
int Player::get_y(){return _y;}
void Player::set_x(const int x){_x = x;}
void Player::set_y(const int y){_y = y;}
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

    if ((_y <= 110) && (_jump == true)) {}
    }

}