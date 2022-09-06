#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "object.h"

class Obstacle : public Object {
public:
  // Constructor
  Obstacle(int x, int y, int w, int h, int screenWidth, int screenHeight,
           int speed);

  // Destructor
  ~Obstacle();

  // Update instance by moving it
  void Update();

  // getter for instance counter
  static long int get_blockCtr() { return _blockCTR; }

private:
  int _speed{1}; // moving speed of obstacles... could be varied with different
                 // game levels later on
  static long int _blockCTR; // static class member for counting instances
};

#endif