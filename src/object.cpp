#include "object.h"

// Constructor with reference y position
Object::Object(int x, int y, int screenHeight)
    : _x(x), _y(y), _screenHeight(screenHeight) {}

// Constructor without reference y position, defaulting to 0
Object::Object(int x, int y, int refLvl, int screenHeight)
    : _x(x), _y(y), _refLvl(refLvl), _screenHeight(screenHeight) {}

int Object::GetAbsHeight() { return _screenHeight - _refLvl - _y; }