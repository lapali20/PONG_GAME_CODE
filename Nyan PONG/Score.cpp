#include "Score.h"

Score::Score()
{
    scoreSurface = NULL;
    scoreTexture = NULL;
}

Score::~Score()
{
    SDL_FreeSurface(scoreSurface);
    scoreTexture = NULL;
}

void Score::setImage(int score, SDL_Renderer* renderer)
{
    switch (score)
    {
    case 0:
        {
            scoreSurface = SDL_LoadBMP("images/score0.bmp");
        }
        break;
    case 1:
        {
            scoreSurface = SDL_LoadBMP("images/score1.bmp");
        }
        break;
    case 2:
        {
            scoreSurface = SDL_LoadBMP("images/score2.bmp");
        }
        break;
    case 3:
        {
            scoreSurface = SDL_LoadBMP("images/score3.bmp");
        }
        break;
    case 4:
        {
            scoreSurface = SDL_LoadBMP("images/score4.bmp");
        }
        break;
    case 5:
        {
            scoreSurface = SDL_LoadBMP("images/score5.bmp");
        }
        break;
    default:
        {
            std::cout << "Score Error" << std::endl;
        }
        break;
    }

    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
}


void Score::setRect(int playerNum)
{
    if (playerNum == 1)
    {
        Area.y = 0;
        Area.x = 328;
        Area.h = 52;
        Area.w = 43;
    }
    else
    {
        Area.y = 0;
        Area.x = 418;
        Area.h = 52;
        Area.w = 43;
    }
}

void Score::displayScore(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, scoreTexture, NULL, &Area);
}
