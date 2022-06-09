#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

const int WIDTH = 100, HEIGHT = 200;

int main( int argc, char *argv[] )
{
    
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow( "Hello SDL World", SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL );

    if(window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    SDL_Event windowEvent;

    while (true)
    {
        if ( SDL_PollEvent(&windowEvent) )
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}