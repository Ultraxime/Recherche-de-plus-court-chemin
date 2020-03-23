#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>

#include "structures.h"
#include "utilitaires.h"
#include "utilitaires_structures.h"
#include "errors.h"

bool init(){

	srand(time(NULL));					//Initialisation pour l'algorithme de random

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

	return true;    
}

List facteurs_premiers(int n){

	if(n <= 1)
		return create_List();

	int i = 2;

	while( n%i != 0 )
		i++;

	return push_value_List( void_of_int(i), facteurs_premiers( n/i ));
}

void pause(){

	bool done = true;

	while(done){

		SDL_Event event;

		while(SDL_PollEvent(&event)){		//On attend un event

			switch(event.type){

				case SDL_KEYDOWN:			//Si une touche a été pressée
					done = false;
					break;

				default :
					break;
			}
		}
	}
}

int* sort(int* value, unsigned int n, unsigned int i){

	int* classement;

	if( i <= 0){
		
		classement = malloc(n * sizeof(int));

		if(classement == NULL){
			printf("Cannot create the table");
			exit(MALLOC_ERROR);
		}

		classement[0] = 0;

		return classement;
	}

	classement = sort(value, n, i-1);

	unsigned int j = 0;

	while( value[classement[j]] < value[i] && j < i )
		j++;

	int tmp = i;

	while(j < i){

		classement[i] = classement[i-1];
		
		i--;
	}

	classement[j] = tmp;

	return classement;

}