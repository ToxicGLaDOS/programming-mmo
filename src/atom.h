#ifndef atom_H
#define atom_H

#include "SDL2/SDL_stdinc.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include "fonts.h"


class atom{
    public:
        atom(SDL_Color color, float x, float y, float radius, std::string text);
        void draw(SDL_Renderer* renderer);
        void update(Uint32 deltaTime);
    private:
        SDL_Color color;
        float x, y, radius;
        std::string text;
};


#endif