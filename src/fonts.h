#ifndef FONTS_H
#define FONTS_H

#include <SDL2/SDL_ttf.h>


class Fonts{
    public:
        static void init();
        static TTF_Font* sans;
};

#endif