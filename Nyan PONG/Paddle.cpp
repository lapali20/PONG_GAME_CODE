#include "Paddle.h"

Paddle::Paddle()
{
    speed = 12;
    AIControlled = false;
}

Paddle::~Paddle()
{
}

void Paddle::setWidth(int newWidth)
{
    hitBox.w = newWidth;
}

void Paddle::setHeight(int newHeight)
{
    hitBox.h = newHeight;
}

void Paddle::setPosX(int newX)
{
    hitBox.x = newX;
}

void Paddle::setPosY(int newY)
{
    hitBox.y = newY;
}

void Paddle::move(int screenH,  SDL_Event& e )
{
    hitBox.y = hitBox.y + dirY;
    int distanceFromBottom = hitBox.y + hitBox.h;

    if(hitBox.y < 0 || distanceFromBottom >= screenH)
    {
        hitBox.y = hitBox.y - dirY;
    }
}

void Paddle::moveAI(int screenH, int ballPosY)
{
    if (ballPosY < hitBox.y + hitBox.h/2)
    {
        hitBox.y = hitBox.y - speed;
    }
    else if(ballPosY > hitBox.y + hitBox.h/2)
    {
        hitBox.y = hitBox.y + speed;
    }

    if(hitBox.y < 0)
    {
        hitBox.y = 0;
    }
    else if(hitBox.y > screenH - hitBox.h)
    {
        hitBox.y = screenH - hitBox.h;
    }
}

void Paddle::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_w: dirY -= speed; break;
            case SDLK_s: dirY += speed; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_w: dirY += speed; break;
            case SDLK_s: dirY -= speed; break;
        }
    }
}

void Paddle::handleEventP2( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: dirY -= speed; break;
            case SDLK_DOWN: dirY += speed; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: dirY += speed; break;
            case SDLK_DOWN: dirY -= speed; break;
        }
    }
}
