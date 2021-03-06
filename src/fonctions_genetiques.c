#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fonctions_genetiques.h" 
#include "utilitaires_structures.h"
#include "errors.h"
#include "constantes.h"
#include "utilitaires.h"
#include "fonctions_cartes.h"


Population first_Population(){

	Population population;

	population = calloc(TAILLE, sizeof(Individu));

	if(population == NULL){
		printf("Cannot create the first population");
		exit(MALLOC_ERROR);
	}

	for(uint16_t i = 0; i < TAILLE; i++)
		population[i] = random_Individu();

	return population;
}

Population evolution(Population original, uint32_t* rank){

	uint16_t kept = 0;

	Population population = calloc(TAILLE, sizeof(Individu));

	if(population == NULL){
		printf("Cannot create the new population");
		exit(MALLOC_ERROR);
	}

	for(uint16_t i = 0; i < TAILLE; i++){

		if(rand() % TAILLE <= TAILLE * exp(-i)){

			population[kept] = original[i];

			kept++;
		}
	}

	for( uint16_t i = kept; i < TAILLE; i++)
		population[i] = wedding(population[rand() % kept], population[rand() % kept]);

	mutation(population);

	free(original);

	return population;
}

Individu wedding(Individu pere, Individu mere){

	return create_Individu( (uint16_t)pere.forward + (uint16_t)mere.forward,
							(uint16_t)pere.right + (uint16_t)mere.right,
							(uint16_t)pere.backward + (uint16_t)mere.backward,
							(uint16_t)pere.left + (uint16_t)mere.left,
							( pere.direction + mere.direction ) / 2);
}

void mutation(Population population){

	for(uint16_t i = 0; i < TAILLE; i++){
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

	uint32_t* scores;

	scores = calloc(TAILLE, sizeof(uint32_t));

	if(scores == NULL){
		printf("Cannot create scores table");
		exit(MALLOC_ERROR);
	}

	Couple couple;

	uint32_t min = LIMITE +1;										//Cela permet d'etre sur de tracer un chemin mais s'il n'est pas intéressant

	List chemin = create_List();

	for(uint16_t i = 0; i < TAILLE; i++){

		#ifdef DEBUG
			if(i%10==0)printf("%d\n", i);
		#endif

		couple = life_simple(map, begin, end, population[i]);

		scores[i] = int32_of_void(couple.key);

		if(scores[i] < min){
			min = scores[i];

			clear_List(chemin);
			chemin = list_of_void(couple.value);
		}else{
			clear_List(list_of_void(couple.value));
		}
	}

	return create_Couple(scores, chemin);
}

Couple life_simple(SimpleMap map, Coordonnee begin, Coordonnee end, Individu individu){

	Coordonnee currentPosition = begin;

	List chemin = create_List();

	uint32_t count = 0;

	while( !is_equal_Coordonnee(currentPosition, end) && count < LIMITE){
		chemin = push_value_List( void_of_Coordonnee(currentPosition), chemin);

		currentPosition = next_step_simple(map, currentPosition, individu);

		count ++;
	}

	chemin = push_value_List( void_of_Coordonnee(currentPosition), chemin);

	return create_Couple( void_of_int32(count), chemin);
}

Coordonnee next_step_simple(SimpleMap map, Coordonnee currentPosition, Individu individu){

	uint16_t x = currentPosition.x;				//Simplification des notations pour alleger le code
	uint16_t y = currentPosition.y;

	uint8_t resultat = rand() % 255;			//Resultat aléatoire que l'on va utiliser pour nos choix de direction

	Coordonnee arrivee = currentPosition;

	if( resultat < individu.forward ){				//On avance

		switch( individu.direction ){

			case 0:							//On pointe vers le nord
				if( y > 0 && !map[x][y-1] ){

					arrivee = create_Coordonnee(x, y-1);

				}
				break;

			case 1:							//On pointe vers l'est
				if( x < N-1 && !map[x+1][y] ){

					arrivee = create_Coordonnee(x+1, y);

				}
				break;

			case 2:							//On pointe vers le sud
				if( y < M-1 && !map[x][y+1] ){

					arrivee = create_Coordonnee(x, y+1);

				}
				break;

			case 3:							//On pointe vers l'ouest
				if( x > 0 && !map[x-1][y] ){

					arrivee = create_Coordonnee(x-1, y);

				}
				break;

			default:
				exit(SWITCH_ERROR);
				break;
		}
	}else{

		resultat -= individu.forward;			//Pour reduire le nombre de calcul a venir

		if( resultat < individu.right ){		//On va a droite

			switch( individu.direction ){
				case 0:							//On pointe vers le nord
					if( x < N-1 && !map[x+1][y] ){

						arrivee = create_Coordonnee(x+1, y);

						individu.direction = 1;			//on pointe desormais vers l'est

					}
					break;

				case 1:							//On pointe vers l'est
					if( y < M-1 && !map[x][y+1] ){

						arrivee = create_Coordonnee(x, y+1);

						individu.direction = 2; 			//On pointe desormais le sud

					}
					break;

				case 2:							//On pointe vers le sud
					if( x > 0 && !map[x-1][y] ){

						arrivee = create_Coordonnee(x-1, y);

						individu.direction = 3;			//On pointe desormais l'ouest

					}
					break;

				case 3:							//On pointe vers l'ouest
					if( y > 0 && !map[x][y-1] ){

						arrivee = create_Coordonnee(x, y-1);

						individu.direction = 0;			//On pointe desormais le nord

					}
					break;

				default:
					exit(SWITCH_ERROR);
					break;
			}

		}else{

			if( resultat < individu.right + individu.backward ){	//On recule

				switch( individu.direction ){
					case 0:							//On pointe vers le nord
						if( y < M-1 && !map[x][y+1] ){

							arrivee = create_Coordonnee(x, y+1);

							individu.direction = 2;			//on pointe desormais vers le sud

						}
						break;

					case 1:							//On pointe vers l'est
						if( x > 0 && !map[x-1][y] ){

							arrivee = create_Coordonnee(x-1, y);

							individu.direction = 3; 			//On pointe desormais l'ouest'

						}
						break;

					case 2:							//On pointe vers le sud
						if( y > 0 && !map[x][y-1] ){

							arrivee = create_Coordonnee(x, y-1);

							individu.direction = 0;			//On pointe desormais le nord

						}
						break;

					case 3:							//On pointe vers l'ouest
						if( x < N-1 && !map[x+1][y] ){

							arrivee = create_Coordonnee(x+1, y);

							individu.direction = 1;			//On pointe desormais l'est

						}
						break;

					default:
						exit(SWITCH_ERROR);
						break;
				}

			}else{						//On va a gauche

				switch( individu.direction ){
					case 0:							//On pointe vers le nord
						if( x > 0 && !map[x-1][y] ){

							arrivee = create_Coordonnee(x-1, y);

							individu.direction = 3;			//on pointe desormais vers l'ouest

						}
						break;

					case 1:							//On pointe vers l'est
						if( y > 0 && !map[x][y-1] ){

							arrivee = create_Coordonnee(x, y-1);

							individu.direction = 0; 			//On pointe desormais le nord

						}
						break;

					case 2:							//On pointe vers le sud
						if( x < N-1 && !map[x+1][y] ){

							arrivee = create_Coordonnee(x+1, y);

							individu.direction = 1;			//On pointe desormais l'est

						}
						break;

					case 3:							//On pointe vers l'ouest
						if( y < M-1 && !map[x][y+1] ){

							arrivee = create_Coordonnee(x, y+1);

							individu.direction = 2;			//On pointe desormais le sud

						}
						break;

					default:
						exit(SWITCH_ERROR);
						break;
				}
			}
		}
	}
	return currentPosition;
}


Couple resultat_genetique_simple(SimpleMap map, SDL_Renderer* renderer, SDL_Texture* texture, Coordonnee begin, Coordonnee end){

	Population population = first_Population();

	List chemin;

	uint32_t min = LIMITE;

	for(uint16_t i = 0; i < NB_GENERATION; i++){

		#ifdef DEBUG
			printf("Génération : %d\n", i );
		#endif

		Couple couple = generation_simple(map, begin, end, population);

		uint32_t* resultats = couple.key;

		uint32_t* rank = sort(resultats, TAILLE, TAILLE-1);

		if(resultats[rank[0]] < min){
			min = resultats[rank[0]];

			clear_List(chemin);
			chemin = list_of_void(couple.value);

			Screen pixels = screen_from_SimpleMap(map);
			draw_coordonnee(begin, pixels, color(255, 255, 255));
			draw_coordonnee(end, pixels, color(0, 0, 0));
			draw_way(chemin, pixels);

			show(renderer, texture, pixels);

			free(pixels);
			
		}else{
			clear_List(list_of_void(couple.value));
		}

		population = evolution(population, rank);

		free(couple.key);

		free(rank);

	}

	return	create_Couple(chemin, void_of_int32(min))	;

}
