#include "object.h"

// Constructor with reference y position
Object::Object(int x, int y, int w, int h, int screenHeight)
    : _x(x), _y(y), _w(w), _h(h), _screenHeight(screenHeight) {}

// Constructor without reference y position, defaulting to 0
Object::Object(int x, int y, int w, int h, int refLvl, int screenHeight)
    : _x(x), _y(y), _w(w), _h(h), _refLvl(refLvl), _screenHeight(screenHeight) {}

int Object::GetAbsHeight() { return _screenHeight - _refLvl - _y; }