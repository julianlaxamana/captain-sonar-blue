#include <button.h>

Button::Button() {}
Button::Button(Renderer* renderer, int textureIndex) {
	this->renderer = renderer;
	this->textureIndex = textureIndex;
}
bool Button::render(double x, double y, double scale, int flags) {
    renderer->drawTexture(textureIndex, x, y, scale, flags);

    SDL_FRect rect;
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(renderer->getWindow(), &windowWidth, &windowHeight);

    double xScale = windowWidth / 800.0;
    double yScale = windowHeight / 600.0;
    double scaleR = (xScale + yScale) / 2.0;
    if (flags & CENTER_V) {
        rect.y = y * windowHeight - ((scale)*renderer->getTexture(textureIndex)->getHeight() * scaleR * renderer->getTexture(textureIndex)->getScale()) / 2;
        rect.h = (scale)*renderer->getTexture(textureIndex)->getHeight() * scaleR * renderer->getTexture(textureIndex)->getScale();
    }
    else {
        rect.y = y * windowHeight;
        rect.h = (scale)*renderer->getTexture(textureIndex)->getHeight() * scaleR * renderer->getTexture(textureIndex)->getScale();
    }

    if (flags & CENTER_H) {
        rect.x = (x)*windowWidth - (scale)*renderer->getTexture(textureIndex)->getWidth() * scaleR * renderer->getTexture(textureIndex)->getScale() / 2;
        rect.w = (scale)*renderer->getTexture(textureIndex)->getWidth() * scaleR * renderer->getTexture(textureIndex)->getScale();
    }
    else {
        rect.x = (x)*windowWidth;
        rect.w = (scale)*renderer->getTexture(textureIndex)->getWidth() * scaleR * renderer->getTexture(textureIndex)->getScale();
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
    else if (prevRelease && !prevClick) { prevRelease = false; return true; }

    if (mouseState & 1) prevClick = true;
    else prevClick = false;

    return false;
}