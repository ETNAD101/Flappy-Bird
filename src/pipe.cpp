#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include "entity.h"
#include "pipe.h"
#include "math.h"

Pipe::Pipe(Vector2f p_pos, SDL_Texture* p_tex)
    :Entity(p_pos, p_tex) 
{   
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 24;
    rect.h = 250;
    this->setCurrentFrame(rect);
}

Pipe::~Pipe()
{

}

void Pipe::scroll()
{
    Vector2f currentPos = this->getPos();
    currentPos.x -= 0.25f;
    this->setPos(currentPos);
}

void Pipe::update()
{
    this->scroll();
}

void Pipe::test()
{
    std::cout << "Works" << std::endl;
}