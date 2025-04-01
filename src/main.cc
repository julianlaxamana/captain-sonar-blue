#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <font.h>
#include <button.h>
#include <renderer.h>
#include <iostream>
using namespace std;



int main(int argc, char* argv[]) {

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    TTF_Init();
    if (!result) 
    {
      SDL_Log("SDL_Init Error: %s", SDL_GetError());
      return -1;
    }

    // Initizalition Stuff
    Renderer sigma("Captain Sonar");
    int title = sigma.createTexture("title.bmp", 0.2);
    int sonar = sigma.createTexture("sonar.bmp", 0.75);

    SDL_Event event;
    int quit = 0;

    Button button(&sigma, title);

    Font bruh = Font("rizz.ttf", 100);
    SDL_Color White = { 255, 255, 255 };

    string chatText = "";
    vector<string> chatHistory;

    while (!quit){
      while (SDL_PollEvent(&event)){
        switch (event.type){
          case SDL_EVENT_QUIT:
            quit = 1;
            break;
          case SDL_EVENT_TEXT_INPUT:
                // Concat User text
                chatText += event.text.text;
              break;

          case SDL_EVENT_KEY_DOWN:
              // Detect when player is done entering text
              if ((event.key.key == SDLK_ESCAPE || event.key.key == SDLK_RETURN) && !chatText.empty()) {
                  // TODO -- VOSS send the text to the server here
                  chatHistory.push_back(chatText);
                   
                  // Clear the text
                  chatText = "";
                  SDL_StopTextInput(sigma.getWindow());
              }
              // Deleting Text
              else if (event.key.key == SDLK_BACKSPACE) {
                  chatText = chatText.substr(0, chatText.size() - 1);
              }
              break;
        }
      }

      // TODO -- VOSS recieve the text from the other clients store it in the history.

      

      // Clear Frame
      sigma.clear();

      // Draw Background at Center of Screen
      sigma.drawTexture(sonar, .5, .5, 1, CENTER_V | CENTER_H);

      // Draw Title
      sigma.drawTexture(title, 0.5, 0.2, 1, CENTER_V | CENTER_H);

      // Button to Enter Text
      if (button.render(.5, .5, 1, CENTER_V | CENTER_H)) {
          SDL_StartTextInput(sigma.getWindow());
      }

      // Render the text
      if (!chatText.empty()) sigma.drawText(chatText, bruh, White, 0.0, 0.0, .3);

      for (int i = 0; i < chatHistory.size(); i++) {
          sigma.drawText(chatHistory.at(chatHistory.size() - i - 1), bruh, White, 0.0, i * 0.05 + 0.05, .25);
      }

      sigma.render();

      SDL_Delay(1);
    }


    return 0;
}
