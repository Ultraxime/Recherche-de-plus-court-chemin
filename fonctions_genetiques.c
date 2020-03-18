#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"
#include "fonctions_genetiques.h" 
#include "utilitaires_structures.h"
#include "errors.h"
#include "constantes.h"


Population first_Population(){

	Population population;

	population = malloc(NB * sizeof(Individu));

	if(population == NULL){
		printf("Cannot create the first population");
		exit(MALLOC_ERROR);
	}

	for(int i = 0; i < NB; i++)
		population[i] = random_Individu();
}

Population evolution(Population original, int* rank){

	int kept = 0;

	Population population = malloc(NB * sizeof(Individu));

	if(population == NULL){
		printf("Cannot create the new population");
		exit(MALLOC_ERROR);
	}

	for(int i = 0; i < NB; i++){

		if(rand() % NB <= exp( -i ) * NB){

			population[kept] = original[i];

			kept++;
		}
	}

	for( int i = kept; i < NB; i++)
		population[i] = wedding(population[rand() % kept], population[rand() % kept]);

	mutation(population);

	return population;
}

Individu wedding(Individu pere, Individu mere){

	return create_Individu( (int)pere.forward + (int)mere.forward,
							(int)pere.right + (int)mere.right,
							(int)pere.backward + (int)mere.backward,
							(int)pere.left + (int)mere.left,
							( pere.direction + mere.direction ) / 2);
}

void mutation(Population population){

	for(int i = 0; i < NB; i++){
		switch(rand() % MUTATION){
			case 0:
				population[i] = create_Individu(rand() % 255,
												population[i].right,
												population[i].backward,
												population[i].left,
												population[i].direction);
				break;
			case 1:
				population[i] = create_Individu(population[i].forward,
												rand() % 255,
												population[i].backward,
												population[i].left,
												population[i].direction);
				break;
			case 2:
				population[i] = create_Individu(population[i].forward,
												population[i].right,
												rand() % 255,
												population[i].left,
												population[i].direction);
				break;
			case 3:
				population[i] = create_Individu(population[i].forward,
												population[i].right,
												population[i].backward,
												rand() % 255,
												population[i].direction);
				break;
			case 4:
				population[i] = create_Individu(population[i].forward,
												population[i].right,
												population[i].backward,
												population[i].left,
												rand() % 4);
				break;
			default:
				break;
		}
	}
}


Couple generation_simple(SimpleMap map, Coordonnee begin, Coordonnee end, Population population){

	unsigned int* scores;

	scores = malloc(NB * sizeof(int));

	if(scores == NULL){
		printf("Cannot create scores table");
		exit(MALLOC_ERROR);
	}

	List* chemins;

	chemins = malloc(NB * sizeof(List));
	
	if(chemins == NULL){
		printf("Cannot create chemin table");
		exit(MALLOC_ERROR);
	}

	for(int i = 0; i < NB; i++){
		Couple couple = life_simple(map, begin, end, population[i]);

		scores[i] = int_of_void(couple.key);

		chemins[i] = list_of_void(couple.value);
	}

	return create_Couple(scores, chemins);
}

Couple life_simple(SimpleMap map, Coordonnee begin, Coordonnee end, Individu individu){

	Coordonnee currentPosition = begin;

	List chemin = create_List();

	int count = 0;

	while( !is_equal_Coordonnee(currentPosition, end) && count < LIMITE){
		chemin = push_value_List( void_of_Coordonnee(currentPosition), chemin);

		currentPosition = next_step_simple(map, currentPosition, individu);

		count ++;
	}

	chemin = push_value_List( void_of_Coordonnee(currentPosition), chemin);

	return create_Couple( void_of_int(count), chemin);
}

Coordonnee next_step_simple(SimpleMap map, Coordonnee currentPosition, Individu individu){

	return currentPosition;
}