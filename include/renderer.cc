#include "renderer.h"
#include <iostream>


Renderer::Renderer() {
	window = SDL_CreateWindow("sdl3", 800, 600, 0);
	if (window == NULL) {
		SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
	}
	renderer = SDL_CreateRenderer(window, NULL);
}
Renderer::Renderer(std::string title) {
    window = SDL_CreateWindow(title.c_str(), 800, 600, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
    }
    this->title = title;
    renderer = SDL_CreateRenderer(window, NULL);
}
Renderer::~Renderer() {
    for (int i = 0; i < textures.size(); i++) {
        delete textures.at(i);
    }
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int Renderer::createTexture(std::string path) {
    // Create Texture
        Texture* texture = new Texture(path, renderer);

        // Add Texture to vector
        textures.push_back(texture);

        // Return Texture Index
        return textures.size() - 1;
}
void Renderer::render() {
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float)(0.5 + 0.5 * SDL_sin(now));
    const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, 1.0f);

    SDL_RenderPresent(renderer);
}
void Renderer::drawTexture(int index, double x1, double x2, double y1, double y2) {
    SDL_RenderClear(renderer);
    SDL_FRect rect;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* blue, full alpha */

    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    rect.x = (x1) * windowWidth;
    rect.y = y1 * windowHeight;
    rect.w = (x2 - x1) * windowWidth;
    rect.h = (y2 - y1) * windowHeight;

    //SDL_RenderFillRect(renderer, &rect);
    SDL_RenderTexture(renderer, textures.at(index)->getTexture(), NULL, &rect);
}