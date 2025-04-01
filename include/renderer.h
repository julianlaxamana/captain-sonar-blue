#pragma once
#include <SDL3/SDL.h>
#include <texture.h>
#include <font.h>
#include <string>
#include <vector>

#define CENTER_V 1
#define CENTER_H 2

class Renderer {
	public:
		Renderer();
		Renderer(std::string title);
		~Renderer();

		int createTexture(std::string path, double scale = 1.0);
		void drawTexture(int index, double x, double y, double scale = 1.0, int flags = 0);
		void drawText(std::string text, Font &font, SDL_Color color, double x, double y, double scale = 1.0, int flags = 0);
		void render();
		void clear();

		bool drawButton(int index, double x, double y, double scale = 1.0, int flags = 0);

		SDL_Window* getWindow() const;
		SDL_Renderer* getRenderer() const;
		Texture* getTexture(int index) const;
	private:
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		std::vector<Texture*> textures;
		std::string title;
		


};