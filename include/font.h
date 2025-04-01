#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>

class Font {
public:
	Font();
	Font(std::string path, float size);
	~Font();
	TTF_Font* getFont() const;
private:
	TTF_Font* font;
	float size;
};