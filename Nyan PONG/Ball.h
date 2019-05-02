#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>

#define PI 3.14

using namespace std;

#include "Object.h"
#include "Paddle.h"

class Ball: public Object
{
public:
    Ball(int x, int y, int dirX, int dirY);
    ~Ball();
    int move(int screenH,  int screenW, Paddle P1, Paddle P2);
    void bounce(Paddle P, int dirNav);
    SDL_Surface* ballSurf;
    SDL_Texture* ballTex;

private:
    int originX, originY, dirCap, negDirCap;
};

#endif
