#include "texture.h"

Texture::Texture() {
}

Texture::Texture(std::string path, SDL_Renderer* renderer) {
    SDL_Surface* surface = NULL;

    surface = SDL_LoadBMP(path.c_str());
    if (surface == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s\n", SDL_GetError());

    texture_width = surface->w;
    texture_height = surface->h;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s\n", SDL_GetError());

    SDL_DestroySurface(surface);
}   

Texture::Texture(std::string path, SDL_Renderer* renderer, double scale) {
    SDL_Surface* surface = NULL;
    this->scale = scale;
    surface = SDL_LoadBMP(path.c_str());
    if (surface == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s\n", SDL_GetError());

    texture_width = surface->w;
    texture_height = surface->h;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s\n", SDL_GetError());

    SDL_DestroySurface(surface);
}

SDL_Texture* Texture::getTexture() const {
    return texture;
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}
int Texture::getWidth() const {
    return texture_width;
}
int Texture::getHeight() const {
    return texture_height;
}

double Texture::getScale() const {
    return scale;
}