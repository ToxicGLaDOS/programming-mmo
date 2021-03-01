#include "fonts.h"

TTF_Font* Fonts::sans = NULL;

void Fonts::init(){
    Fonts::sans = TTF_OpenFont("../FreeSans.ttf", 120); //this opens a font style and sets a size
    if (Fonts::sans == NULL){
        printf("Couldn't load font. SDL ERROR: %s\n", TTF_GetError());
    }
}