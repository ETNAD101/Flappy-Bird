#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include "pipe.h"
#include "entity.h"
#include "math.h"

class Player : public Entity
{
public:
    Player(Vector2f p_pos, SDL_Texture* p_tex);
    void setVelocity(Vector2f p_vel);
    bool checkColided(Pipe& p_target);
    Vector2f getVelocity();
    void move(Vector2f p_vel);
    void update();
private:
    const float GRAVITY = 0.03;
    Vector2f velocity;
};