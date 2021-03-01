#include "atom.h"
#include "fonts.h"

atom::atom(SDL_Color color, float x, float y, float radius, std::string text) :
color{color}, x{x}, y{y}, radius{radius}, text{text} {

}

void atom::draw(SDL_Renderer* renderer){
    int err = filledCircleRGBA(renderer, x, y, radius, (Sint16)color.r, (Sint16)color.g, (Sint16)color.b, (Sint16)color.a);
    SDL_Surface* surfaceText = TTF_RenderText_Solid(Fonts::sans, text.c_str(), {0,0,0});

    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_Rect textRect;
    textRect.h = radius/5;
    textRect.w = radius/5;
    textRect.x = x - textRect.w/2;
    textRect.y = y - textRect.h/2;
    SDL_RenderCopy(renderer, text, NULL, &textRect);
}

void atom::update(Uint32 deltaTime){
    float speed = 0.1f;
    x += speed * deltaTime;
}