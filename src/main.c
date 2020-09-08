#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "utilitaires_structures.h"
#include "fonctions_cartes.h"
#include "fonctions_genetiques.h"
#include "errors.h"
#include "utilitaires.h"
#include "constantes.h"

int main(int argc, char** argv){

	arg_parser(argc, argv);

	if(!init()){
		printf("Error during initialization");
		return INIT_ERROR;
	}

	SDL_Surface* screen = SDL_SetVideoMode(N ,M , 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);//|SDL_FULLSCREEN);
    if ( !screen )
    {
        printf("Unable to set %dx%d video: %s\n", N, M, SDL_GetError());
        return INIT_ERROR;
    }

    SDL_WM_SetCaption("Recherche de plus court chemin", NULL);
	
	DrawableMap map = bruit_Perlin_DrawableMap();

	Coordonnee begin;

	begin  = random_Coordonnee(N, M);

	while( map[begin.x][begin.y] >= altitude)									//On ne peut debuter sur la terre
		begin = random_Coordonnee(N, M);

	Coordonnee end;

	end = random_Coordonnee(N, M);

	while( map[end.x][end.y] >=altitude || is_equal_Coordonnee(begin, end))	//On ne peut finir sur terre et avoir un debut egal a une fin n'a pas d'interet
		end = random_Coordonnee(N, M);


	draw_DrawableMap(map, screen, begin, end);

	SimpleMap map2 = simpleMap_from_DrawableMap(map);

	draw_SimpleMap(map2, screen, begin, end);

	pause();

	Couple genetique = resultat_genetique_simple(map2, begin, end, screen);

	return 0;
}
