#ifndef OBJECT_H
#define OBJECT_H

class Object {

public:
  // Constructors and Destructor
  Object(int x, int y, int w, int h, int screenHeight);
  Object(int x, int y, int w, int h, int refLvl, int screenHeight);
  ~Object();

  // getters and setters
  int get_x();
  int get_y();
  int get_width();
  int get_height();
  virtual void set_x(const int x);
  virtual void set_y(const int y);

  int GetAbsHeight();

protected:
  int _x, _y;
  int _w{0}, _h{0};
  int _screenHeight;
  int _refLvl{0};
};

#endif