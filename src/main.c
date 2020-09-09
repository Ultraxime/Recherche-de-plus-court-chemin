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

	if (verbose) {
	    printf(VERBOSE_NAME_COLOR "Altitude" COLOR_RESET ": %d\n", altitude);
	    printf(VERBOSE_NAME_COLOR "Population size" COLOR_RESET ": %d\n", population_size);
	    printf(VERBOSE_NAME_COLOR "Number of generation" COLOR_RESET ": %d\n", nb_generation);
	    printf(VERBOSE_NAME_COLOR "Probability of mutation" COLOR_RESET ": %d\n", mutation_probability);
	}

	if(!init()){
		printf("Error during initialization");
		return INIT_ERROR;
	}

	SDL_Window* screen = SDL_CreateWindow("Recherche de plus court chemin", 
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											map_width, map_height,
											SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    if ( !screen )
    {
        printf("Unable to set %dx%d video: %s\n", map_width, map_height, SDL_GetError());
        return INIT_ERROR;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, 0);

    if( !renderer )
    {
    	printf("Unable to set %dx%d renderer: %s\n", map_width, map_height, SDL_GetError());
    	return INIT_ERROR;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");   //Permet de travailler sur une ecran NxM quelque soit la résolution
	SDL_RenderSetLogicalSize(renderer, map_width, map_height);				//Le GPU se chargeant de convertir en la bonne taille d'ecran

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 		//create a black screen as a start
	SDL_RenderClear(renderer); 
	SDL_RenderPresent(renderer);

	SDL_Texture* texture = SDL_CreateTexture(renderer, 			//Creation de la texture qui sera utilisé pour les affichages successifs
                               SDL_PIXELFORMAT_ARGB8888, 
                               SDL_TEXTUREACCESS_STREAMING, 
                               map_width, map_height);


	DrawableMap map = bruit_Perlin_DrawableMap();

	Coordonnee begin;

	begin  = random_Coordonnee(map_width, map_height);

	while( map[begin.x][begin.y] >= altitude)									//On ne peut debuter sur la terre
		begin = random_Coordonnee(map_width, map_height);

	Coordonnee end;

	end = random_Coordonnee(map_width, map_height);

	while( map[end.x][end.y] >=altitude || is_equal_Coordonnee(begin, end))	//On ne peut finir sur terre et avoir un debut egal a une fin n'a pas d'interet
		end = random_Coordonnee(map_width, map_height);

	Screen pixels = screen_from_DrawableMap(map);
	draw_coordonnee(begin, pixels, color(255, 255, 255));
	draw_coordonnee(end, pixels, color(0, 0, 0));

	show(renderer, texture, pixels);

	free(pixels);

	SimpleMap map2 = simpleMap_from_DrawableMap(map);

	pixels = screen_from_SimpleMap(map2);
	draw_coordonnee(begin, pixels, color(255, 255, 255));
	draw_coordonnee(end, pixels, color(0, 0, 0));

	show(renderer, texture, pixels);

	free(pixels);

	Couple genetique = resultat_genetique_simple(map2, renderer, texture, begin, end);

	return 0;
}
