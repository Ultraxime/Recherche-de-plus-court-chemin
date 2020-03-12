#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "fonctions_cartes.h"
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


DrawableMap random_DrawableMap(int n, int m //Dimension de la carte a créer
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

		if(i%pasN == O){

			for(int j = 0 ; j < m ; j++){
				if(j%pasM == O)
					map[i][j] = rand() % 255;
				else
					map[i][j] = 0;
			}
		}else{
			for(int j = 0 ; < m ; j++)
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

DrawableMap bruit_Perlin_DrawableMap(int n; int m){

	//On choisit comme largeur pour les cartes temporraire entre n ou n+1 comme celui dont le précedent a le plus de diviseurs premiers

	List divN = facteurs_premiers(n-1);
	List divN1 = facteurs_premiers(n);

	int largeur = 0;
	
	if( len_List(divN) > len_List(divN1) ){

		clear_List(divN1);

		largeur = n;
	}else{

		clear_List(divN);

		divN = divN1;

		largeur = n+1;
	}

	//On fait la même chose pour la longueur

	List divM = facteurs_premiers(m-1);
	List divM1 = facteurs_premiers(m);

	int longueur = 0;

	if( len_List(divM) > len_List(divM1) ){

		clear_List(divM1);

		longueur = m;
	}else{

		clear_List(divM);

		divM = divM1;

		longueur = m+1;
	}

	//Creation de carte avec des gradiants de plus en plus fin

	int pasN = largeur - 1;
	int pasM = longeur - 1;

	List maps = random_DrawableMap(largeur, longueur, pasN, pasM);			//Creation de la List qui contiendra les cartes à sommer

	while(!is_empty_List(divN) && !is_empty_List(divM)){
		
		if(pasN < pasM)
			pasM /= pop_List( &divM );
		else
			pasN *= pop_List( &divN );

		maps = push_value_List( random_DrawableMap(largeur, longueur, pasN, pasM), maps);
	}

	while( !is_empty_List(divN) ){

		pasN /= pop_List( &divN );

		maps = push_value_List( random_DrawableMap(largeur, longueur, pasN, pasM), maps);	
	}

	while( !is_empty_List(divM) ){

		pasM /= pop_List( &divM );

		maps = push_value_List( random_DrawableMap(largeur, longueur, pasN, pasM), maps);
	}

	DrawableMap tmpMap = pop_List( &maps );

	LongMap longMap = NULL;

	longMap = malloc(n*sizeof(long*));

	if(longMap == NULL){
		printf("Cannot create main table\n");
		error(MALLOC_ERROR);
	}

	unsigned long puissance = 1;

	for(int i = 0; i < n; i++){

		longMap[i] = malloc(m*sizeof(long));

		if(longMap[i] == NULL){
			printf("Cannot create table %d\n", i);
			error(MALLOC_ERROR);
		}

		for(int j = 0; j < m; j++)

			longMap[i][j] = puissance * (unsigned long) tmpMap[i][j];
	}

	clear_DrawableMap(tmpMap, largeur);

	while( !is_empty_List(maps) ){
	
		tmpMap = pop_List( &maps );

		for(int)

	}
}