#ifndef OBJECT_H
#define OBJECT_H

class Object {

public:
  Object(int x, int y, int w, int h, int screenHeight);
  Object(int x, int y, int w, int h, int refLvl, int screenHeight);
  int GetAbsHeight();

protected:
  int _x, _y;
  int _w{0}, _h{0};
  int _screenHeight;
  int _refLvl{0};
};

#endif