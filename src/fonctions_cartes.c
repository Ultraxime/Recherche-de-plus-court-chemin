#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "structures.h"
#include "fonctions_cartes.h"
#include "utilitaires_structures.h"
#include "utilitaires.h"
#include "errors.h"
#include "constantes.h"

uint8_t altitude = DEFAULT_ALTITUDE;
uint16_t map_width = DEFAULT_MAP_WIDTH;
uint16_t map_height = DEFAULT_MAP_HEIGHT;

SimpleMap simpleMap_from_DrawableMap(DrawableMap origin){

	SimpleMap map = NULL;

	map = malloc(map_width * sizeof(bool*));

	if (map == NULL) {
		printf("Cannot create the main table\n");
		exit(MALLOC_ERROR);
	}

	for (uint16_t i = 0; i < map_width; i++) {

		map[i] = malloc(map_height * sizeof(bool));

		if (map[i] == NULL) {
			printf("Cannot create table %d\n",i);
			exit(MALLOC_ERROR);
		}

		for(uint16_t j = 0 ; j < map_height ; j++)

			map[i][j] = origin[i][j] > altitude;			//si l'altitude le permet cette case represente de la terre, de la mer sinon
	}

	return map;
}


DrawableMap random_DrawableMap(int n, int m, //Dimension de la carte a créer
								int pasN, int pasM ){//pas pour le gradient
	DrawableMap map = NULL;

	map = malloc(n*sizeof(char*));

	if(map == NULL){
		printf("Cannot create the main table\n");
		exit(MALLOC_ERROR);
	}

	for(int i = 0 ; i < n ; i++){

		map[i] = malloc(m*sizeof(char));

		if(map[i] == NULL){
			printf("Cannot create table %d\n",i);
			exit(MALLOC_ERROR);
		}

		if(i%pasN == 0){

			for(int j = 0 ; j < m ; j++){
				if(j%pasM == 0)
					map[i][j] = rand() % 255;
				else
					map[i][j] = 0;
			}
		}else{
			for(int j = 0 ; j < m ; j++)
				map[i][j] = 0;
		}
	}

	for(int i = 0; i < n; i+=pasN){
		
		for(int k = 0; k < m - 1 ; k+=pasM){

			for(int j = 1; j < pasM; j++){

				map[i][k+j] = (unsigned char) ( ( j * (unsigned int) map[i][ k + pasM ] + (pasM - j) * (unsigned int) map[i][k]) / pasM );			//barycentre des point aléatoire pour obtenir un grandient sur les lignes avec les aléas

			}
		}
	}

	for(int j = 0; j < m; j++){

		for(int k = 0; k < n - 1 ; k+=pasN){

			for(int i = 1; i < pasN; i++){

				map[k+i][j] = (unsigned char) ( ( i * (unsigned int) map[ k + pasN ][j] + (pasN - i) * (unsigned int) map[k][j] ) / pasN );			//barycentre sur les colonnes
			}
		}
	}

	return map;
}

DrawableMap bruit_Perlin_DrawableMap(){

	//On choisit comme largeur pour les cartes temporraire entre n ou n+1 comme celui dont le précedent a le plus de diviseurs premiers

	List divN1 = facteurs_premiers(map_width - 1);
	List divN2 = facteurs_premiers(map_width);

	List divN;

	uint16_t n = 0;
	
	if ( len_List(divN1) > len_List(divN2) ) {

		clear_List(divN2);

		divN = divN1;

		n = map_width;

	} else {

		clear_List(divN1);

		divN = divN2;

		n = map_width + 1;
	}

	//On fait la même chose pour la longueur

	List divM1 = facteurs_premiers(map_height - 1);
	List divM2 = facteurs_premiers(map_height);

	List divM;

	uint16_t m = 0;

	if ( len_List(divM1) > len_List(divM2) ) {

		clear_List(divM2);

		divM = divM1;

		m = map_height;

	} else {

		clear_List(divM1);

		divM = divM2;

		m = map_height + 1;
	}

	//Creation de carte avec des gradiants de plus en plus fin

	int pasN = n - 1;
	int pasM = m - 1;

	List maps = create_Element( random_DrawableMap(n, m, pasN, pasM) );			//Creation de la List qui contiendra les cartes à sommer

	while(!is_empty_List(divN) && !is_empty_List(divM)){
		
		if(pasN < pasM)
			pasM /= int_of_void( pop_List( &divM ) );
		else
			pasN /= int_of_void( pop_List( &divN ) );

		maps = push_value_List( random_DrawableMap(n, m, pasN, pasM), maps);
	}

	while( !is_empty_List(divN) ){

		pasN /= int_of_void( pop_List( &divN ) );

		maps = push_value_List( random_DrawableMap(n, m, pasN, pasM), maps);	
	}

	while( !is_empty_List(divM) ){

		pasM /= int_of_void( pop_List( &divM ) );

		maps = push_value_List( random_DrawableMap(n, m, pasN, pasM), maps);
	}

	DrawableMap tmpMap = drawableMap_of_void( pop_List( &maps ) );

	LongMap longMap = NULL;

	longMap = malloc(map_width * sizeof(long*));

	if (longMap == NULL) {
		printf("Cannot create main table\n");
		exit(MALLOC_ERROR);
	}

	unsigned long puissance = 1;

	for (uint16_t i = 0; i < map_width; i++) {

		longMap[i] = malloc(map_height * sizeof(long));

		if (longMap[i] == NULL) {
			printf("Cannot create table %d\n", i);
			exit(MALLOC_ERROR);
		}

		for (uint16_t j = 0; j < map_height; j++)

			longMap[i][j] = puissance * (unsigned long) tmpMap[i][j];
	}

	puissance += PUISSANCE;

	
	clear_DrawableMap(tmpMap, n);

	while( !is_empty_List(maps) ){
	
		tmpMap = drawableMap_of_void( pop_List( &maps ) );

		for(uint16_t i = 0; i < map_width; i++)

			for(uint16_t j = 0; j < map_height; j++)

				longMap[i][j] += puissance * (unsigned long) tmpMap[i][j];

		clear_DrawableMap(tmpMap, n);

		puissance += PUISSANCE;
	}

	unsigned long min = min_LongMap(longMap, map_width, map_height);

	unsigned long max = max_LongMap(longMap, map_width, map_height) - min;

	DrawableMap map = NULL;

	map = malloc(map_width * sizeof(char*));

	if (map == NULL) {
		printf("Cannot create the main table\n");
		exit(MALLOC_ERROR);
	}

	for (uint16_t i = 0; i < map_width; i++) {

		map[i] = malloc(map_height * sizeof(char));

		if ( map[i] == NULL ) {
			printf("Cannot create table %d\n", i);
			exit(MALLOC_ERROR);
		}

		for (uint16_t j = 0; j < map_height; j++)

			map[i][j] = (unsigned char) ( ( 255 * (longMap[i][j] - min)) / max );
	}

	clear_LongMap(longMap, map_width);

	return map;
}

void draw_DrawableMap(DrawableMap map, SDL_Surface* screen, Coordonnee begin, Coordonnee end){

	if(SDL_LockSurface(screen) < 0 ){
        printf("Unable to lock screen : %s\n", SDL_GetError());
        exit(LOCK_SURFACE_ERROR);
    }

    Uint32 *pixels;
    pixels = screen->pixels;

    Uint32 darkBlue = SDL_MapRGB(screen->format, 70, 169, 224);
    Uint32 blue = SDL_MapRGB(screen->format, 160, 203, 237);
    Uint32 lightBlue = SDL_MapRGB(screen->format, 213, 234, 248);
    
    Uint32 green = SDL_MapRGB(screen->format, 167, 210, 101);
    Uint32 lightOrange = SDL_MapRGB(screen->format, 254, 240, 191);
    Uint32 orange = SDL_MapRGB(screen->format, 251, 207, 112);
    Uint32 brown = SDL_MapRGB(screen->format, 243, 159, 20);

    for (uint16_t i = 0; i < map_width; i++) {

    	for (uint16_t j = 0; j < map_height; j++) {

    		if (map[i][j] < altitude / 4) {
    			
    			pixels[j*map_width + i] = darkBlue;
    		
    		} else if(map[i][j] < (3 * (unsigned int) altitude ) / 4) {

    			pixels[j*map_width + i] = blue;

    		} else if(map[i][j] < altitude) {

    			pixels[j*map_width + i] = lightBlue;

    		} else if(map[i][j] > 255 - (255 - altitude) / 8) {

    			pixels[j*map_width + i] = brown;
    			
    		} else if(map[i][j] > 255 - (255 - altitude) / 2) {

    			pixels[j*map_width + i] = orange;
    			
    		} else if(map[i][j] > 255 - (3 * (unsigned int) (255 - altitude) ) / 4) {

    			pixels[j*map_width + i] = lightOrange;
    			
    		} else {

    			pixels[j*map_width + i] = green;

    		}
    	}
    }

    Uint32 begin_color = SDL_MapRGB(screen->format, 255, 255, 0);

    draw_coordonnee(begin, pixels, begin_color);

    Uint32 end_color = SDL_MapRGB(screen->format, 0, 0, 0);

    draw_coordonnee(end, pixels, end_color);

    SDL_UnlockSurface(screen);

    SDL_Flip(screen);

    pause();

}


void draw_SimpleMap(SimpleMap map, SDL_Surface* screen, Coordonnee begin, Coordonnee end){

	if(SDL_LockSurface(screen) < 0 ){
        printf("Unable to lock screen : %s\n", SDL_GetError());
        exit(LOCK_SURFACE_ERROR);
    }

    Uint32 *pixels;
    pixels = screen->pixels;

    Uint32 blue = SDL_MapRGB(screen->format, 160, 203, 237);
    
    Uint32 green = SDL_MapRGB(screen->format, 167, 210, 101);
    
    for (uint16_t i = 0; i < map_width; i++) {

    	for (uint16_t j = 0; j < map_height; j++) {

    		if ( map[i][j] ) {
    			
    			pixels[j*map_width + i] = green;

    		} else {

    			pixels[j*map_width + i] = blue;

    		}
    	}
    }

    Uint32 begin_color = SDL_MapRGB(screen->format, 255, 255, 0);

    draw_coordonnee(begin, pixels, begin_color);

    Uint32 end_color = SDL_MapRGB(screen->format, 0, 0, 0);

    draw_coordonnee(end, pixels, end_color);

    SDL_UnlockSurface(screen);

    SDL_Flip(screen);

}

void draw_way(List way, SDL_Surface* screen){

	if(SDL_LockSurface(screen) < 0 ){
        printf("Unable to lock screen : %s\n", SDL_GetError());
        exit(LOCK_SURFACE_ERROR);
    }

    Coordonnee coordonnee;

	Uint32 *pixels;
    pixels = screen->pixels;

    Uint32 color = SDL_MapRGB(screen->format, 255, 0, 0);

	while(!is_empty_List(way)){
		coordonnee = coordonnee_of_void(pop_List(&way));
		draw_coordonnee(coordonnee, pixels, color);
	}

	SDL_UnlockSurface(screen);

    SDL_Flip(screen);

}

void draw_coordonnee(Coordonnee coordonnee, Uint32* pixels, Uint32 color){

	pixels[coordonnee.x + coordonnee.y * map_width ] = color;
	pixels[coordonnee.x+1 + coordonnee.y * map_width ] = color;
	pixels[coordonnee.x-1 + coordonnee.y * map_width ] = color;
	pixels[coordonnee.x + coordonnee.y * map_width + map_width ] = color;
	pixels[coordonnee.x+1 + coordonnee.y * map_width + map_width ] = color;
	pixels[coordonnee.x-1 + coordonnee.y * map_width + map_width ] = color;
	pixels[coordonnee.x + coordonnee.y * map_width - map_width ] = color;
	pixels[coordonnee.x+1 + coordonnee.y * map_width - map_width ] = color;
	pixels[coordonnee.x-1 + coordonnee.y * map_width - map_width ] = color;
}
