#include "object.h"

Object::Object(int x, int y, int screenHeight): _x(x), _y(y), _screenHeight(screenHeight){}

int Object::GetAbsHeight() {
    return _screenHeight - _y;

}