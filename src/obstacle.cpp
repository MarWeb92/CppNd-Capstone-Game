#include "obstacle.h"
#include "object.h"

long int Obstacle::_blockCTR = 0;

Obstacle::Obstacle(int x, int y, int width, int height, int screenWidth,
                   int screenHeight, int speed)
    : Object(x, y, screenHeight), _width(width), _height(height), _speed(speed) {
        _blockCTR++;
    }

void Obstacle::Update() {
    _x = _x - _speed;
}
