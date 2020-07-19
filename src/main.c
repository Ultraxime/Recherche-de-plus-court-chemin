#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "utilitaires_structures.h"
#include "fonctions_cartes.h"
#include "fonctions_genetiques.h"
#include "errors.h"
#include "utilitaires.h"
#include "constantes.h"

int main(){

	if(!init()){
		printf("Error during initialization");
		return INIT_ERROR;
	}

	SDL_Window* screen = SDL_CreateWindow("Recherche de plus court chemin", 
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											N ,M,
											SDL_WINDOW_FULLSCREEN_DESKTOP);
    if ( !screen )
    {
        printf("Unable to set %dx%d video: %s\n", N, M, SDL_GetError());
        return INIT_ERROR;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, 0);

    if( !renderer )
    {
    	printf("Unable to set %dx%d renderer: %s\n", N, M, SDL_GetError());
    	return INIT_ERROR;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");   //Permet de travailler sur une ecran NxM pour le code
	SDL_RenderSetLogicalSize(renderer, N, M);				//Le GPU se chargeant de convertir en la bonne taille d'ecran

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 		//create a black screen as a start
	SDL_RenderClear(renderer); 
	SDL_RenderPresent(renderer);

	DrawableMap map = bruit_Perlin_DrawableMap();

	Coordonnee begin;

	begin  = random_Coordonnee(N, M);

	while( map[begin.x][begin.y] >= H)									//On ne peut debuter sur la terre
		begin = random_Coordonnee(N, M);

	Coordonnee end;

	end = random_Coordonnee(N, M);

	while( map[end.x][end.y] >=H || is_equal_Coordonnee(begin, end))	//On ne peut finir sur terre et avoir un debut egal a une fin n'a pas d'interet
		end = random_Coordonnee(N, M);


	draw_DrawableMap(map, renderer, begin, end);

	SimpleMap map2 = simpleMap_from_DrawableMap(map);

	draw_SimpleMap(map2, renderer, begin, end);

	pause();

	Couple genetique = resultat_genetique_simple(map2, renderer, begin, end);

	return 0;
}