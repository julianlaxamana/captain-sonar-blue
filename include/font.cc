#include "font.h"

Font::Font(){}

Font::Font(std::string path, float size) {
		font = TTF_OpenFont(path.c_str(), size);
		if (font == NULL) SDL_Log("SDL_Font Error: %s", SDL_GetError());
		this->size = size;
}
	Font::~Font() {
		TTF_CloseFont(font);
	}


	TTF_Font* Font::getFont() const {
		return font;
	}