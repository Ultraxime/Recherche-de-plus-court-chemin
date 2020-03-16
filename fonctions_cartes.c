#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "structures.h"
#include "fonctions_cartes.h"
#include "utilitaires_structures.h"
#include "utilitaires.h"
#include "errors.h"
#include "constantes.h"

SimpleMap simpleMap_from_DrawableMap(DrawableMap origin, int n, int m){

	SimpleMap map = NULL;

	map = malloc(n*sizeof(bool*));

	if(map == NULL){
		printf("Cannot create the main table\n");
		exit(MALLOC_ERROR);
	}

	for(int i = 0 ; i < n ; i++){

		map[i] = malloc(m*sizeof(bool));

		if(map[i] == NULL){
			printf("Cannot create table %d\n",i);
			exit(MALLOC_ERROR);
		}

		for(int j = 0 ; j < m ; j++)

			map[i][j] = origin[i][j] > H;			//si l'altitude le permet cette case represente de la terre, de la mer sinon
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
		
		for(int k = 0; k < m; k+=pasM){

			for(int j = 1; j < pasM; j++){

				map[i][k+j] = (unsigned char) ( ( j * (unsigned int) map[i][ k + pasM ] + (pasM - j) * (unsigned int) map[i][k]) / pasM );			//barycentre des point aléatoire pour obtenir un grandient sur les lignes avec les aléas

			}
		}
	}

	for(int j = 0; j < m; j++){

		for(int k = 0; k < n; k+=pasN){

			for(int i = 1; i< pasN; i++){

				map[k+i][j] = (unsigned char) ( ( i * (unsigned int) map[ k + pasN][j] + (pasN - i) * (unsigned int) map[k][j] ) / pasN );			//barycentre sur les colonnes
			}
		}
	}

	return map;
}

DrawableMap bruit_Perlin_DrawableMap(int n, int m){

	//On choisit comme largeur pour les cartes temporraire entre n ou n+1 comme celui dont le précedent a le plus de diviseurs premiers

	List divN1 = facteurs_premiers(n-1);
	List divN2 = facteurs_premiers(n);

	List divN;

	int largeur = 0;
	
	if( len_List(divN1) > len_List(divN2) ){

		clear_List(divN2);

		divN = divN1;

		pause();

		largeur = n;

	}else{

		clear_List(divN1);

		divN = divN2;

		pause();

		largeur = n+1;
	}

	//On fait la même chose pour la longueur

	List divM1 = facteurs_premiers(m-1);
	List divM2 = facteurs_premiers(m);

	List divM;

	int longueur = 0;

	if( len_List(divM1) > len_List(divM2) ){

		clear_List(divM2);

		divM = divM1;

		longueur = m;

	}else{

		clear_List(divM1);

		divM = divM2;

		longueur = m+1;
	}

	pause();

	//Creation de carte avec des gradiants de plus en plus fin

	int pasN = largeur - 1;
	int pasM = longueur - 1;

	List maps = create_Element( random_DrawableMap(largeur, longueur, pasN, pasM) );			//Creation de la List qui contiendra les cartes à sommer

	while(!is_empty_List(divN) && !is_empty_List(divM)){
		
		if(pasN < pasM)
			pasM /= int_of_void( pop_List( &divM ) );
		else
			pasN /= int_of_void( pop_List( &divN ) );

		maps = push_value_List( random_DrawableMap(largeur, longueur, pasN, pasM), maps);
	}

	while( !is_empty_List(divN) ){

		pasN /= int_of_void( pop_List( &divN ) );

		maps = push_value_List( random_DrawableMap(largeur, longueur, pasN, pasM), maps);	
	}

	while( !is_empty_List(divM) ){

		pasM /= int_of_void( pop_List( &divM ) );

		maps = push_value_List( random_DrawableMap(largeur, longueur, pasN, pasM), maps);
	}

	DrawableMap tmpMap = drawableMap_of_void( pop_List( &maps ) );

	LongMap longMap = NULL;

	longMap = malloc(n*sizeof(long*));

	if(longMap == NULL){
		printf("Cannot create main table\n");
		exit(MALLOC_ERROR);
	}

	unsigned long puissance = 1;

	for(int i = 0; i < n; i++){

		longMap[i] = malloc(m*sizeof(long));

		if(longMap[i] == NULL){
			printf("Cannot create table %d\n", i);
			exit(MALLOC_ERROR);
		}

		for(int j = 0; j < m; j++)

			longMap[i][j] = puissance * (unsigned long) tmpMap[i][j];
	}

	puissance +=PUISSANCE;

	clear_DrawableMap(tmpMap, largeur);

	while( !is_empty_List(maps) ){
	
		tmpMap = drawableMap_of_void( pop_List( &maps ) );

		for(int i = 0; i < n; i++)

			for(int j = 0; j < m; j++)

				longMap[i][j] += puissance * (unsigned long) tmpMap[i][j];

		clear_DrawableMap(tmpMap, largeur);

		puissance += PUISSANCE;
	}

	unsigned long min = min_LongMap(longMap, n, m);

	unsigned long max = max_LongMap(longMap, n, m) - min;

	DrawableMap map = NULL;

	map = malloc(n*sizeof(char*));

	if(map == NULL){
		printf("Cannot create the main table\n");
		exit(MALLOC_ERROR);
	}

	for(int i = 0; i < n; i++){

		map[i] = malloc(m*sizeof(char));

		if( map[i] == NULL ){
			printf("Cannot create table %d\n", i);
			exit(MALLOC_ERROR);
		}

		for(int j = 0; j < m; j++)

			map[i][j] = (unsigned char) ( ( 255 * (longMap[i][j] - min)) / max );
	}

	clear_LongMap(longMap, n);

	return map;
}

void draw_DrawableMap(DrawableMap map, int n, int m, SDL_Surface* screen, Coordonnee begin, Coordonnee end){

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

    for(int i = 0; i < n; i++){

    	for(int j = 0; j < m; j++){

    		if(map[i][j] < H / 4){
    			
    			pixels[i*m + j] = darkBlue;
    		
    		}else if(map[i][j] < (3 * (unsigned int) H ) / 4){

    			pixels[i*m + j] = blue;

    		}else if(map[i][j] < H){

    			pixels[i*m + j] = lightBlue;

    		}else if(map[i][j] > 255 - (255 - H) / 8){

    			pixels[i*m + j] = brown;
    			
    		}else if(map[i][j] > 255 - (255 - H) / 2){

    			pixels[i*m + j] = orange;
    			
    		}else if(map[i][j] > 255 - (3 * (unsigned int) (255 - H) ) / 4){

    			pixels[i*m + j] = lightOrange;
    			
    		}else{

    			pixels[i*m + j] = green;

    		}
    	}
    }

    SDL_UnlockSurface(screen);

    SDL_Flip(screen);

}