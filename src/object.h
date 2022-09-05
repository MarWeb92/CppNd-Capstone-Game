#ifndef OBJECT_H
#define OBJECT_H

class Object {

public:
  Object(int x, int y, int screenHeight);
  Object(int x, int y, int refLvl, int screenHeight);
  int GetAbsHeight();

protected:
  int _x, _y;
  int _screenHeight;
  int _refLvl{0};
};

#endif