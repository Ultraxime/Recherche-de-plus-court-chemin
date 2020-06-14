#ifndef FONCTIONS_CARTES_H_INCLUDED
#define FONCTIONS_CARTES_H_INCLUDED

#include <SDL/SDL.h>

#include "structures.h"

SimpleMap simpleMap_from_DrawableMap(DrawableMap);

DrawableMap bruit_Perlin_DrawableMap();

DrawableMap random_DrawableMap(int, int, int, int);

void draw_DrawableMap(DrawableMap, SDL_Surface*, Coordonnee, Coordonnee);

void draw_SimpleMap(SimpleMap, SDL_Surface*, Coordonnee, Coordonnee);

void draw_way(List, SDL_Surface*);

void draw_coordonnee(Coordonnee, Uint32*, Uint32);

#endif