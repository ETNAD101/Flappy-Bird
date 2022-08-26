#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include "player.h"
#include "pipe.h"
#include "entity.h"
#include "math.h"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex)
    :Entity(p_pos, p_tex) 
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 16;
    rect.h = 16;
    this->setCurrentFrame(rect);
}

void Player::setVelocity(Vector2f p_vel)
{
    velocity = p_vel;
}

bool Player::checkColided(Pipe& p_target)
{
    if (this->getPos().x + this->getCurrentFrame().w >= p_target.getPos().x &&    
        this->getPos().x <= p_target.getPos().x + p_target.getCurrentFrame().w && 
        this->getPos().y + this->getCurrentFrame().h >= p_target.getPos().y &&    
        this->getPos().y <= p_target.getPos().y + p_target.getCurrentFrame().h)
    { 
        return true;
    }
    return false;
}

Vector2f Player::getVelocity()
{
    return velocity;
}

void Player::move(Vector2f p_vel)
{
    Vector2f currentPos = this->getPos();
    currentPos = currentPos + p_vel;
    this->setPos(currentPos);
}

void Player::update()
{   
    if (this->getPos().y + (velocity.y + GRAVITY) >= 295)
    {   
        velocity.y = 0;      
    }
    else
    {
        velocity.y += GRAVITY;
    }

    if (this->getPos().y + velocity.y <= 0)
    {
        velocity.y = 0;
    }
    this->move(Vector2f(velocity.x, velocity.y));
}