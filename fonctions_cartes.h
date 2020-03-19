#ifndef FONCTIONS_CARTES_H_INCLUDED
#define FONCTIONS_CARTES_H_INCLUDED

#include <SDL/SDL.h>

#include "structures.h"

SimpleMap simpleMap_from_DrawableMap(DrawableMap, int, int);

DrawableMap bruit_Perlin_DrawableMap(int, int,SDL_Surface*);

DrawableMap random_DrawableMap(int, int, int, int);

void draw_DrawableMap(DrawableMap, int, int, SDL_Surface*, Coordonnee, Coordonnee);

#endif