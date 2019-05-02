#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Score
{
public:
    Score();
    ~Score();
    SDL_Rect Area;
    void setImage(int score, SDL_Renderer* renderer);
    void displayScore(SDL_Renderer* renderer);
    void setRect(int playerNum);

    SDL_Surface* scoreSurface;
    SDL_Texture* scoreTexture;

};
#endif
