#include "obstacle.h"
#include "object.h"

// initializing static class member for counting created instances
long int Obstacle::_blockCTR = 0;

// Constructor, incrementing the counter
Obstacle::Obstacle(int x, int y, int w, int h, int screenWidth,
                   int screenHeight, int speed)
    : Object(x, y, w, h, screenHeight), _speed(speed) {
  _blockCTR++;
}

// Destructor, no action needed at the moment
Obstacle::~Obstacle() {}

// Update the obstacles by moving them with a dedicated speed
void Obstacle::Update() { _x = _x - _speed; }
