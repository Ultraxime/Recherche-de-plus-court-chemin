#ifndef FONCTIONS_GENETIQUES_H_INCLUDED
#define FONCTIONS_GENETIQUES_H_INCLUDED

#include <SDL/SDL.h>

#include "structures.h"

void set_nb_generation(uint32_t);

Population first_Population();

Population evolution(Population, int*);

Individu wedding(Individu, Individu);

void mutation(Population);

Couple generation_simple(SimpleMap, Coordonnee, Coordonnee, Population);

Couple life_simple(SimpleMap, Coordonnee, Coordonnee, Individu);

Coordonnee next_step_simple(SimpleMap, Coordonnee, Individu);

Couple resultat_genetique_simple(SimpleMap, Coordonnee, Coordonnee, SDL_Surface*);

#endif
