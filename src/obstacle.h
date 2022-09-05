#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "object.h"

class Obstacle : public Object {
public:
  Obstacle(int x, int y, int w, int h, int screenWidth,
           int screenHeight, int speed);

  void Update();

  int get_width() {return _w;}
  int get_height() {return _h;}
  int get_x() {return _x;}
  int get_y() {return _y;}
  static long int get_blockCtr() {return _blockCTR;}

private:
  int _speed{1};
  static long int _blockCTR;
};

#endif