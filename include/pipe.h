#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <entity.h>
#include <math.h>

class Pipe : public Entity
{
public:
    Pipe(Vector2f p_pos, SDL_Texture* p_tex);
    ~Pipe();
    void scroll();
    void update();
    void test();
};