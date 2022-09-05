#include "obstacle.h"
#include "object.h"

Obstacle::Obstacle(int x, int y, int width, int height, int screenWidth,
                   int screenHeight, int speed)
    : Object(x, y, screenHeight), _width(width), _height(height), _speed(speed) {}

void Obstacle::Update() {
    _x = _x - _speed;
}