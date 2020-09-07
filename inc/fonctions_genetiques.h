#ifndef FONCTIONS_GENETIQUES_H_INCLUDED
#define FONCTIONS_GENETIQUES_H_INCLUDED

#include <SDL2/SDL.h>

#include "structures.h"



Population first_Population();

Population evolution(Population, uint32_t*);

Individu wedding(Individu, Individu);

void mutation(Population);

Couple generation_simple(SimpleMap, Coordonnee, Coordonnee, Population);

Couple life_simple(SimpleMap, Coordonnee, Coordonnee, Individu);

Coordonnee next_step_simple(SimpleMap, Coordonnee, Individu);

Couple resultat_genetique_simple(SimpleMap, SDL_Renderer*, SDL_Texture*, Coordonnee, Coordonnee);

#endif
