#include "Object.h"

Object::Object()
{
	hitBox.w = 0;
	hitBox.h = 0;
	hitBox.x = 0;
	hitBox.y = 0;

	dirX = 0;
	dirY = 0;
}

Object::~Object()
{
}
