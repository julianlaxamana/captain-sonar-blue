#pragma once
#include <SDL3/SDL.h>
#include <texture.h>
#include <string>
#include <vector>

class Renderer {
	public:
		Renderer();
		Renderer(std::string title);
		~Renderer();

		int createTexture(std::string path);
		void drawTexture(int index, double x1, double x2, double y1, double y2);
		void render();

	private:
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		std::vector<Texture*> textures;
		std::string title;
		


};