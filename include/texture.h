#pragma once
#include <SDL3/SDL.h>
#include <string>


class Texture {
public:
	Texture();
	Texture(std::string path, SDL_Renderer* renderer = NULL);
	~Texture();

	SDL_Texture* getTexture() const;
private:
	SDL_Texture* texture = NULL;
	int texture_width;
	int texture_height;

};