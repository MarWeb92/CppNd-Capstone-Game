#include "obstacle.h"
#include "object.h"

long int Obstacle::_blockCTR = 0;

Obstacle::Obstacle(int x, int y, int w, int h, int screenWidth,
                   int screenHeight, int speed)
    : Object(x, y,w,h, screenHeight), _speed(speed) {
        _blockCTR++;
    }

void Obstacle::Update() {
    _x = _x - _speed;
}
