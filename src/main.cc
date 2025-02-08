#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (!result) 
    {
      SDL_Log("SDL_Init Error: %s", SDL_GetError());
      return -1;
    }

    window = SDL_CreateWindow("sdl3 hello world", 800, 600, 0);
    if (window == NULL){
      SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
      return -2;
    }

    SDL_Event event;
    int quit = 0;
    renderer = SDL_CreateRenderer(window, NULL);
    while (!quit){
      while (SDL_PollEvent(&event)){
        switch (event.type){
          case SDL_EVENT_QUIT:
            quit = 1;
            break;
        }
      }
     const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
      SDL_SetRenderDrawColorFloat(renderer, red, green, blue, 1.0f);
      SDL_RenderClear(renderer);
      SDL_FRect rect;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);  /* blue, full alpha */
    rect.x = rect.y = 100;
    rect.w = 440;
    rect.h = 280;
    SDL_RenderFillRect(renderer, &rect);

  

      SDL_RenderPresent(renderer);
      SDL_Delay(1);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
