#ifndef PONG_H
#define PONG_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include "Paddle.h"
#include "Ball.h"
#include "SDL_ttf.h"
#include "Score.h"
#include "SDL_image.h"
#include <ctime>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Pong
{
public:
    Pong();
    ~Pong();
    bool initialize();
    void showHome();
    void showTutorial();
    // void replay();
    void runGame();
    void closeGame();
    void processInput(SDL_Event& e);
    void setPaddles(bool isAI);
    void colorChange(int& change, int& choice);
private:
    bool paddleOpp, quit;
    int scoreP1, scoreP2;

    Paddle playerOne;
    Paddle playerTwo;

    Score scoreDisplayP1;
    Score scoreDisplayP2;

    Mix_Music* Nyan_Song;

    SDL_Window* gWindow;
    SDL_Renderer* renderer;
    SDL_Surface* winSurface;
    SDL_Texture* winTexture;
    SDL_Surface* dash;
    SDL_Texture* dashTex;
    SDL_Rect dashRect;
};

#endif
