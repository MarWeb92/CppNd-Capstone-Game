#ifndef OBJECT_H
#define OBJECT_H

class Object {

public:
  Object(int x, int y, int screenHeight);
  int GetAbsHeight();

protected:
  int _x, _y;
  int _screenHeight;
};

#endif