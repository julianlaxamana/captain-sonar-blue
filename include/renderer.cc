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

int Renderer::createTexture(std::string path, double scale) {
    // Create Texture
        Texture* texture = new Texture(path, renderer, scale);

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
void Renderer::clear() {
    SDL_RenderClear(renderer);

}
void Renderer::drawTexture(int index, double x, double y, double scale, int flags) {
    SDL_FRect rect;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* blue, full alpha */

    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    
    double xScale = windowWidth / 800.0;
    double yScale = windowHeight / 600.0;
    double scaleR = (xScale + yScale) / 2.0;
    if (flags & CENTER_V) {
        rect.y = y * windowHeight - ((scale)*textures.at(index)->getHeight() * scaleR * textures.at(index)->getScale()) / 2;
        rect.h = (scale)*textures.at(index)->getHeight() * scaleR * textures.at(index)->getScale();
    }
    else {
        rect.y = y * windowHeight;
        rect.h = (scale)*textures.at(index)->getHeight() * scaleR * textures.at(index)->getScale();
    }

    if (flags & CENTER_H) {
        rect.x = (x)*windowWidth - (scale)*textures.at(index)->getWidth() * scaleR * textures.at(index)->getScale() / 2;
        rect.w = (scale)*textures.at(index)->getWidth() * scaleR * textures.at(index)->getScale();
    }
    else {
        rect.x = (x)*windowWidth;
        rect.w = (scale)*textures.at(index)->getWidth() * scaleR * textures.at(index)->getScale();
    }

    //SDL_RenderFillRect(renderer, &rect);
    SDL_RenderTexture(renderer, textures.at(index)->getTexture(), NULL, &rect);
}

void Renderer::drawText(std::string text, Font& font, SDL_Color color, double x, double y, double scale, int flags) {
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font.getFont(), text.c_str(), text.size(), color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_FRect rect;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* blue, full alpha */

    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);


    double xScale = windowWidth / 800.0;
    double yScale = windowHeight / 600.0;
    double scaleR = (xScale + yScale) / 2.0;
    if (flags & CENTER_V) {
        rect.y = y * windowHeight - ((scale)*surfaceMessage->h * scaleR) / 2;
        rect.h = (scale)*surfaceMessage->h * scaleR ;
    }
    else {
        rect.y = y * windowHeight;
        rect.h = (scale)*surfaceMessage->h * scaleR ;
    }

    if (flags & CENTER_H) {
        rect.x = (x)*windowWidth - (scale)*surfaceMessage->w * scaleR / 2;
        rect.w = (scale)*surfaceMessage->w * scaleR;
    }
    else {
        rect.x = (x)*windowWidth;
        rect.w = (scale)*surfaceMessage->w * scaleR ;
    }

    SDL_RenderTexture(renderer, Message, NULL, &rect);

    SDL_DestroySurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

bool Renderer::drawButton(int index, double x, double y, double scale, int flags) {
    this->drawTexture(index, x, y, scale, flags);

    SDL_FRect rect;
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    double xScale = windowWidth / 800.0;
    double yScale = windowHeight / 600.0;
    double scaleR = (xScale + yScale) / 2.0;
    if (flags & CENTER_V) {
        rect.y = y * windowHeight - ((scale)*textures.at(index)->getHeight() * scaleR * textures.at(index)->getScale()) / 2;
        rect.h = (scale)*textures.at(index)->getHeight() * scaleR * textures.at(index)->getScale();
    }
    else {
        rect.y = y * windowHeight;
        rect.h = (scale)*textures.at(index)->getHeight() * scaleR * textures.at(index)->getScale();
    }

    if (flags & CENTER_H) {
        rect.x = (x)*windowWidth - (scale)*textures.at(index)->getWidth() * scaleR * textures.at(index)->getScale() / 2;
        rect.w = (scale)*textures.at(index)->getWidth() * scaleR * textures.at(index)->getScale();
    }
    else {
        rect.x = (x)*windowWidth;
        rect.w = (scale)*textures.at(index)->getWidth() * scaleR * textures.at(index)->getScale();
    }

    float mouseX, mouseY;
    int mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    static bool prevClick = false;
    static bool prevRelease = false;
    
    if ((mouseState & 1) && (mouseX > rect.x && mouseX < rect.x + rect.w && mouseY > rect.y && mouseY < rect.y + rect.h) && !prevClick) {
        prevClick = true;
        prevRelease = true;
        return false;
    }
    else if (prevRelease && !prevClick) { return true; }

    if (mouseState & 1) prevClick = true;
    else prevClick = false;

    return false;

}

SDL_Window* Renderer::getWindow() const { return window; }
SDL_Renderer* Renderer::getRenderer() const { return renderer; }
Texture* Renderer::getTexture(int index) const { return textures.at(index); }