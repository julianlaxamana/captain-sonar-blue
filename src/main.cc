#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <button.h>
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
    int title = sigma.createTexture("title.bmp", 0.3);
    int sonar = sigma.createTexture("sonar.bmp", 0.75);

    SDL_Event event;
    int quit = 0;

    Button button(&sigma, title);

    bool test = false;
    while (!quit){

      while (SDL_PollEvent(&event)){
        switch (event.type){
          case SDL_EVENT_QUIT:
            quit = 1;
            break;
        }
      }

      sigma.clear();

      float mouseX, mouseY;
      int mouseState = SDL_GetMouseState(&mouseX, &mouseY);

      // Draw Background at Center of Screen
      sigma.drawTexture(sonar, .5, .5, 1, CENTER_V | CENTER_H);
      sigma.drawTexture(title, 0.5, 0.2, 1, CENTER_V | CENTER_H);
      if (button.render(.5, .5, 1, CENTER_V | CENTER_H)) {
          cout << "hi" << endl;
          test = true;
      }
      else cout  << endl;

      sigma.render();

      SDL_Delay(1);
    }

    return 0;
}
