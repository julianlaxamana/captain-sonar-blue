#pragma once
#include <SDL3/SDL.h>
#include <renderer.h>
#include <texture.h>

class Button {
public:
	Button();
	Button(Renderer* renderer, int textureIndex);
	bool render( double x, double y, double scale, int flags);

private:
	int textureIndex;
	Renderer* renderer;



};