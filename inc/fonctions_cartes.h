#ifndef FONCTIONS_CARTES_H_INCLUDED
#define FONCTIONS_CARTES_H_INCLUDED

#include <SDL2/SDL.h>

#include "structures.h"

SimpleMap simpleMap_from_DrawableMap(DrawableMap);

DrawableMap bruit_Perlin_DrawableMap();

DrawableMap random_DrawableMap(uint16_t, uint16_t, uint16_t, uint16_t);

Screen screen_from_DrawableMap(DrawableMap);

Screen screen_from_SimpleMap(SimpleMap);

void draw_way(List, Screen);

void draw_coordonnee(Coordonnee, Screen, Uint32);

void show(SDL_Renderer*, SDL_Texture*, Screen);

#endif
