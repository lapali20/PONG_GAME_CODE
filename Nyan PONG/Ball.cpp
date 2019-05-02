#include "Ball.h"

Ball::Ball(int x = 0, int y = 0, int dirx = 0, int diry = 0)
{
    hitBox.x = x ;
    hitBox.y = y ;
    originX = x;
    originY = y;

    hitBox.h = 30;
    hitBox.w = 45;

    dirX = dirx;
    dirY = diry;

    dirCap = 10;
    negDirCap = -10;
}

Ball::~Ball()
{
    SDL_FreeSurface(ballSurf);
}

int Ball::move(int screenH, int screenW, Paddle P1, Paddle P2)
{
    //1 = playerOne gets a point, 2 = playerTwo gets a point
    int PlayerPoint = 0;

    hitBox.y += dirY;
    hitBox.x += dirX;

    if(hitBox.x <= (P1.hitBox.x + P1.hitBox.w) - 10 )
    {
        //is it above or below the paddle
        if (hitBox.y <= P1.hitBox.y - hitBox.h || hitBox.y >= (P1.hitBox.y + P1.hitBox.h))
        {
            PlayerPoint = 2; //player 2 gets the point
            hitBox.x = originX;
            hitBox.y = originY;
        }
        else //bounce off of P1
        {
            dirX = -dirX;

            if (hitBox.y < (P1.hitBox.y + P1.hitBox.h / 2)) //it is above, so add some velocity
            {
                bounce(P1, 1);
            }
            else //it is below, so subtract some velocity
            {
                bounce(P1, 2);
            }
        }
    }

    else if(hitBox.x >= (P2.hitBox.x - P2.hitBox.w) - 10)
    {
        //is it above or below the paddle
        if (hitBox.y <= P2.hitBox.y - hitBox.h || hitBox.y >= (P2.hitBox.y + P2.hitBox.h))
        {
            PlayerPoint = 1; //player 2 gets the point
            hitBox.x = originX;
            hitBox.y = originY;
        }
        else //bounce off of P2
        {
            dirX = -dirX;

            if (hitBox.y < (P2.hitBox.y + P2.hitBox.h / 2)) //it is above, so add some velocity
            {
                bounce(P2, 1);
            }
            else //it is below, so subtract some velocity
            {
                bounce(P2, 2);
            }
        }
    }
    // bounce
    else if(hitBox.y <= 0 || hitBox.y >= (screenH - hitBox.h))
    {
        dirY = -dirY;
    }

    return PlayerPoint;
}

void Ball::bounce(Paddle P, int dirNav)
{
    int adjust = P.hitBox.y + P.hitBox.h / 2;

    //if it hits the center
    if (hitBox.y == (P.hitBox.y + P.hitBox.h / 2))
    {
        dirY = 0;
        return;
    }

    //while it is not at center, adjust to fit
    if (dirNav == 1)
    {
        while (adjust > hitBox.y)
        {
            adjust--;
        }
    }
    else
    {
        while (adjust < hitBox.y)
        {
            adjust++;
        }
    }
    adjust = adjust / 40;

    if (adjust < 0)
    {
        adjust = 1;
    }

    if (dirNav == 1) // the ball on the top of the paddle
    {
        dirY = adjust;

        if (dirY < negDirCap)
        {
            dirY = negDirCap;
        }
    }
    else
    {
        dirY = adjust;

        if (dirY > dirCap)
        {
            dirY = dirCap;
        }
    }
}
