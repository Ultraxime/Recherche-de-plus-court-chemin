#ifndef FONCTIONS_CARTES_H_INCLUDED
#define FONCTIONS_CARTES_H_INCLUDED

#include "strucures.h"

SimpleMap simpleMap_from_DrawableMap(DrawableMap, int, int);

DrawableMap bruit_perlin_DrawableMap(int, int);

DrawableMap random_DrawableMap(int, int, int, int);


#endif