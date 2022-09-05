#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "object.h"

class Obstacle : public Object {
public:
  Obstacle(int x, int y, int width, int height, int screenWidth,
           int screenHeight, int speed);

  void Update();

  int get_width() {return _width;}
  int get_height() {return _height;}
  int get_x() {return _x;}
  int get_y() {return _y;}

private:
  int _speed{1};
  int _width{0};
  int _height{0};
};

#endif