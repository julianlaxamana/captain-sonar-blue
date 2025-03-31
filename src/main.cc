#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <renderer.h>
#include <iostream>
using namespace std;



int main(int argc, char* argv[]) {

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (!result) 
    {
      SDL_Log("SDL_Init Error: %s", SDL_GetError());
      return -1;
    }

    Renderer sigma("Captain Sonar");
    sigma.createTexture("minecraft.bmp");

    SDL_Event event;
    int quit = 0;

    while (!quit){
      while (SDL_PollEvent(&event)){
        switch (event.type){
          case SDL_EVENT_QUIT:
            quit = 1;
            break;
        }
      }
      sigma.drawTexture(0, 0.1, .5, .1, .5);
      sigma.render();

      SDL_Delay(1);
    }

    return 0;
}
