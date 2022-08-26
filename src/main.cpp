#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <random>
#include "renderWindow.h"
#include "math.h"
#include "entity.h"
#include "player.h"
#include "pipe.h"
#include "settings.h"

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed, ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed, ERROR: " << SDL_GetError() << std::endl;
}

int main(int argc, char* argv[])
{
    init();
    
    // Random Numbers
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(-220, -20); // distribution in range [1, 100]

    

    RenderWindow window(TITLE, WIDTH, HEIGHT);
    SDL_Texture* background = window.loadTexture(BKGND_PATH);
    SDL_Texture* topPipe = window.loadTexture(PIPE_TOP_PATH);
    SDL_Texture* bottomPipe = window.loadTexture(PIPE_BOTTOM_PATH);
    Player player(Vector2f(0, 150), window.loadTexture(PLAYER_PATH));
    

    std::vector<Pipe> topPipes = 
    {
        Pipe(Vector2f(140, -105), topPipe), 
        Pipe(Vector2f(220, -105), topPipe), 
        Pipe(Vector2f(300, -105), topPipe), 
        Pipe(Vector2f(380, -105), topPipe) 
    };

    std::vector<Pipe> bottomPipes = 
    {
        Pipe(Vector2f(140, 205), bottomPipe),
        Pipe(Vector2f(220, 205), bottomPipe),
        Pipe(Vector2f(300, 205), bottomPipe),
        Pipe(Vector2f(380, 205), bottomPipe)
    };

    

    bool run = true;
    SDL_Event event;
    int jumps = 0;

    while(run)
    {   
        while(SDL_PollEvent(&event))
        {   
            if(event.type == SDL_QUIT)
            {
                run = false;
                break;
            }

            if(event.type == SDL_KEYDOWN && jumps == 0)
            {   
                player.setVelocity(Vector2f(0, -1.25));
                jumps++;
            }
            else if (event.type == SDL_KEYUP)
            {
                jumps = 0;
            }
        }

        window.clear();
        window.background(background);
        player.update();
        for (Pipe& p : topPipes)
        {     
            if(p.getPos().x < -20)
            {  
                topPipes.erase(topPipes.begin());
                bottomPipes.erase(bottomPipes.begin());
                int h = dist6(rng); 
                topPipes.push_back(Pipe(Vector2f(300, h), topPipe));
                bottomPipes.push_back(Pipe(Vector2f(300, h + 310), bottomPipe));
            }
            else
            {
                if (player.checkColided(p))
                {
                    topPipes = 
                        {
                            Pipe(Vector2f(140, -105), topPipe), 
                            Pipe(Vector2f(220, -105), topPipe), 
                            Pipe(Vector2f(300, -105), topPipe), 
                            Pipe(Vector2f(380, -105), topPipe) 
                        };

                    bottomPipes = 
                        {
                            Pipe(Vector2f(140, 205), bottomPipe),
                            Pipe(Vector2f(220, 205), bottomPipe),
                            Pipe(Vector2f(300, 205), bottomPipe),
                            Pipe(Vector2f(380, 205), bottomPipe)
                        };
                }
                p.update();
                window.render(p);
            }   
        }

        for (Pipe& p : bottomPipes)
        {
            if (player.checkColided(p))
            {
                topPipes = 
                    { 
                        Pipe(Vector2f(140, -100), topPipe), 
                        Pipe(Vector2f(220, -100), topPipe), 
                        Pipe(Vector2f(300, -100), topPipe), 
                        Pipe(Vector2f(380, -100), topPipe) 
                    };
                    
                bottomPipes = 
                    {
                        Pipe(Vector2f(140, 200), bottomPipe),
                        Pipe(Vector2f(220, 200), bottomPipe),
                        Pipe(Vector2f(300, 200), bottomPipe),
                        Pipe(Vector2f(380, 200), bottomPipe)
                    };
            }
            p.update();
            window.render(p);
        }
        window.render(player);
        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}