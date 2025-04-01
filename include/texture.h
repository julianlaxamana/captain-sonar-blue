#pragma once
#include <SDL3/SDL.h>
#include <string>


class Texture {
public:
	Texture();
	Texture(std::string path, SDL_Renderer* renderer);
	Texture(std::string path, SDL_Renderer* renderer, double scale);
	~Texture();

	SDL_Texture* getTexture() const;
	int getWidth() const;
	int getHeight() const;
	double getScale() const;
private:
	SDL_Texture* texture = NULL;
	int texture_width;
	int texture_height;
	double scale = 1.0;

};