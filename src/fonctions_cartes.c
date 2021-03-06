#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "structures.h"
#include "fonctions_cartes.h"
#include "utilitaires_structures.h"
#include "utilitaires.h"
#include "errors.h"
#include "constantes.h"

SimpleMap simpleMap_from_DrawableMap(DrawableMap origin){

	SimpleMap map = NULL;

	map = calloc(N,sizeof(bool*));

	if(map == NULL){
		printf("Cannot create the main table\n");
		exit(MALLOC_ERROR);
	}

	for(uint16_t i = 0 ; i < N ; i++){

		map[i] = calloc(M,sizeof(bool));

		if(map[i] == NULL){
			printf("Cannot create table %d\n",i);
			exit(MALLOC_ERROR);
		}

		for(uint16_t j = 0 ; j < M ; j++)

			map[i][j] = origin[i][j] > H;			//si l'altitude le permet cette case represente de la terre, de la mer sinon
	}

	return map;
}


DrawableMap random_DrawableMap(uint16_t n, uint16_t m, //Dimension de la carte a créer
								uint16_t pasN, uint16_t pasM ){//pas pour le gradient
	DrawableMap map = NULL;

	map = calloc(n,sizeof(uint8_t*));

	if(map == NULL){
		printf("Cannot create the main table\n");
		exit(MALLOC_ERROR);
	}

	for(uint16_t i = 0 ; i < n ; i++){

		map[i] = calloc(m,sizeof(uint8_t));

		if(map[i] == NULL){
			printf("Cannot create table %d\n",i);
			exit(MALLOC_ERROR);
		}

		if(i%pasN == 0){

			for(uint16_t j = 0 ; j < m ; j++){
				if(j%pasM == 0)
					map[i][j] = rand() % 255;
				else
					map[i][j] = 0;
			}
		}else{
			for(uint16_t j = 0 ; j < m ; j++)
				map[i][j] = 0;
		}
	}

	for(uint16_t i = 0; i < n; i+=pasN){
		
		for(uint16_t k = 0; k < m - 1 ; k+=pasM){

			for(uint16_t j = 1; j < pasM; j++){

				map[i][k+j] = (uint8_t) ( ( j * (uint16_t) map[i][ k + pasM ] + (pasM - j) * (uint16_t) map[i][k]) / pasM );			//barycentre des point aléatoire pour obtenir un grandient sur les lignes avec les aléas

			}
		}
	}

	for(uint16_t j = 0; j < m; j++){

		for(uint16_t k = 0; k < n - 1 ; k+=pasN){

			for(uint16_t i = 1; i < pasN; i++){

				map[k+i][j] = (uint8_t) ( ( i * (uint16_t) map[ k + pasN ][j] + (pasN - i) * (uint16_t) map[k][j] ) / pasN );			//barycentre sur les colonnes
			}
		}
	}

	return map;
}

DrawableMap bruit_Perlin_DrawableMap(){

	//On choisit comme largeur pour les cartes temporraire entre n ou n+1 comme celui dont le précedent a le plus de diviseurs premiers

	List divN1 = facteurs_premiers(N-1);
	List divN2 = facteurs_premiers(N);

	List divN;

	uint16_t n = 0;
	
	if( len_List(divN1) > len_List(divN2) ){

		clear_List(divN2);

		divN = divN1;

		n = N;

	}else{

		clear_List(divN1);

		divN = divN2;

		n = N+1;
	}

	//On fait la même chose pour la longueur

	List divM1 = facteurs_premiers(M-1);
	List divM2 = facteurs_premiers(M);

	List divM;

	uint16_t m = 0;

	if( len_List(divM1) > len_List(divM2) ){

		clear_List(divM2);

		divM = divM1;

		m = M;

	}else{

		clear_List(divM1);

		divM = divM2;

		m = M+1;
	}

	//Creation de carte avec des gradiants de plus en plus fin

	uint16_t pasN = n - 1;
	uint16_t pasM = m - 1;

	List maps = create_Element( random_DrawableMap(n, m, pasN, pasM) );			//Creation de la List qui contiendra les cartes à sommer

	while(!is_empty_List(divN) && !is_empty_List(divM)){
		
		if(pasN < pasM)
			pasM /= int16_of_void( pop_List( &divM ) );
		else
			pasN /= int16_of_void( pop_List( &divN ) );

		maps = push_value_List( random_DrawableMap(n, m, pasN, pasM), maps);
	}

	while( !is_empty_List(divN) ){

		pasN /= int16_of_void( pop_List( &divN ) );

		maps = push_value_List( random_DrawableMap(n, m, pasN, pasM), maps);	
	}

	while( !is_empty_List(divM) ){

		pasM /= int16_of_void( pop_List( &divM ) );

		maps = push_value_List( random_DrawableMap(n, m, pasN, pasM), maps);
	}

	DrawableMap tmpMap = drawableMap_of_void( pop_List( &maps ) );

	LongMap longMap = NULL;

	longMap = calloc(N,sizeof(uint64_t*));

	if(longMap == NULL){
		printf("Cannot create main table\n");
		exit(MALLOC_ERROR);
	}

	uint64_t puissance = 1;

	for(uint16_t i = 0; i < N; i++){

		longMap[i] = calloc(M,sizeof(uint64_t));

		if(longMap[i] == NULL){
			printf("Cannot create table %d\n", i);
			exit(MALLOC_ERROR);
		}

		for(uint16_t j = 0; j < M; j++)

			longMap[i][j] = puissance * (uint64_t) tmpMap[i][j];
	}

	puissance +=PUISSANCE;

	
	clear_DrawableMap(tmpMap, n);

	while( !is_empty_List(maps) ){
	
		tmpMap = drawableMap_of_void( pop_List( &maps ) );

		for(uint16_t i = 0; i < N; i++)

			for(uint16_t j = 0; j < M; j++)

				longMap[i][j] += puissance * (uint64_t) tmpMap[i][j];

		clear_DrawableMap(tmpMap, n);

		puissance += PUISSANCE;
	}

	uint64_t min = min_LongMap(longMap, N, M);

	uint64_t max = max_LongMap(longMap, N, M) - min;

	DrawableMap map = NULL;

	map = calloc(N,sizeof(uint8_t*));

	if(map == NULL){
		printf("Cannot create the main table\n");
		exit(MALLOC_ERROR);
	}

	for(uint16_t i = 0; i < N; i++){

		map[i] = calloc(M,sizeof(uint8_t));

		if( map[i] == NULL ){
			printf("Cannot create table %d\n", i);
			exit(MALLOC_ERROR);
		}

		for(uint16_t j = 0; j < M; j++)

			map[i][j] = (uint8_t) ( ( 255 * (longMap[i][j] - min)) / max );
	}

	clear_LongMap(longMap, N);

	return map;
}

Screen screen_from_DrawableMap(DrawableMap map){

	Screen pixels;
    pixels = calloc( N*M, sizeof(Uint32));
 
    if( !pixels ){
    	printf("Unable to allocate the memory for the screen");
    	exit(MALLOC_ERROR);
    }

    Uint32 darkBlue = color(70, 169, 224);
    Uint32 blue = color(160, 203, 237);
    Uint32 lightBlue = color(213, 234, 248);
    
    Uint32 green = color(167, 210, 101);
    Uint32 lightOrange = color(254, 240, 191);
    Uint32 orange = color(251, 207, 112);
    Uint32 brown = color(243, 159, 20);

    for(uint16_t i = 0; i < N; i++){

    	for(uint16_t j = 0; j < M; j++){

    		if(map[i][j] < H / 4){
    			
    			pixels[j*N + i] = darkBlue;
    		
    		}else if(map[i][j] < (3 * (uint16_t) H ) / 4){

    			pixels[j*N + i] = blue;

    		}else if(map[i][j] < H){

    			pixels[j*N + i] = lightBlue;

    		}else if(map[i][j] > 255 - (255 - H) / 8){

    			pixels[j*N + i] = brown;
    			
    		}else if(map[i][j] > 255 - (255 - H) / 2){

    			pixels[j*N + i] = orange;
    			
    		}else if(map[i][j] > 255 - (3 * (uint16_t) (255 - H) ) / 4){

    			pixels[j*N + i] = lightOrange;
    			
    		}else{

    			pixels[j*N + i] = green;

    		}
    	}
    }

    return pixels;
}


Screen screen_from_SimpleMap(SimpleMap map){


    Screen pixels;
    pixels = calloc( N*M, sizeof(Uint32));

    if( !pixels ){
    	printf("Unable to alloc the memory for the screen");
    	exit(MALLOC_ERROR);
    }

    Uint32 blue = color(160, 203, 237);
    
    Uint32 green = color(167, 210, 101);
    
    for(uint16_t i = 0; i < N; i++){

    	for(uint16_t j = 0; j < M; j++){

    		if( map[i][j] ){
    			
    			pixels[j*N + i] = green;

    		}else{

    			pixels[j*N + i] = blue;

    		}
    	}
    }

    return pixels;

}

void draw_way(List way, Screen pixels){

    Coordonnee coordonnee;

    Uint32 red = color(255, 0, 0);

	while(!is_empty_List(way)){
		coordonnee = coordonnee_of_void(pop_List(&way));
		draw_coordonnee(coordonnee, pixels, red);
	}

}

void draw_coordonnee(Coordonnee coordonnee, Screen pixels, Uint32 color){

	pixels[coordonnee.x + coordonnee.y*N] = color;
	pixels[coordonnee.x+1 + coordonnee.y*N] = color;
	pixels[coordonnee.x-1 + coordonnee.y*N] = color;
	pixels[coordonnee.x + coordonnee.y*N+N] = color;
	pixels[coordonnee.x+1 + coordonnee.y*N+N] = color;
	pixels[coordonnee.x-1 + coordonnee.y*N+N] = color;
	pixels[coordonnee.x + coordonnee.y*N-N] = color;
	pixels[coordonnee.x+1 + coordonnee.y*N-N] = color;
	pixels[coordonnee.x-1 + coordonnee.y*N-N] = color;
}

void show(SDL_Renderer* renderer, SDL_Texture* texture, Screen pixels){

	SDL_UpdateTexture(texture, NULL, pixels, N * sizeof(Uint32) );
	SDL_RenderClear(renderer); 
    SDL_RenderCopy(renderer, texture, NULL, NULL); 
    SDL_RenderPresent(renderer);

    pause();

}
