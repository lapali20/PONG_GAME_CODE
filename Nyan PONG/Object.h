#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

class Object
{
    public:

		Object();
		~Object();

		int dirX, dirY;

		SDL_Rect hitBox;
};

#endif
