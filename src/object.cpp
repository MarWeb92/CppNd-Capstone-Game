#include "object.h"

// Constructor with reference y position
Object::Object(int x, int y, int w, int h, int screenHeight)
    : _x(x), _y(y), _w(w), _h(h), _screenHeight(screenHeight) {}

// Constructor without reference y position, defaulting to 0
Object::Object(int x, int y, int w, int h, int refLvl, int screenHeight)
    : _x(x), _y(y), _w(w), _h(h), _refLvl(refLvl), _screenHeight(screenHeight) {
}

// Destructor
Object::~Object() {}

// getters and setters of Object attributes
int Object::get_x() { return _x; }
int Object::get_y() { return _y; }
int Object::get_width() { return _w; }
int Object::get_height() { return _h; }
void Object::set_x(const int x) { _x = x; }
void Object::set_y(const int y) { _y = y; }

int Object::GetAbsHeight() { return _screenHeight - _refLvl - _y; }