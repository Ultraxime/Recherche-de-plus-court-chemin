#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

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

    pthread_t* interruptionT = NULL;

    while( pthread_create(interruptionT, NULL, interruption, NULL))

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // make sure all thread are shut down before exit
    atexit(cleaning_thread);

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

int* sort(int* value, int n, int i){

	int* classement;

	if( i >= n ) return sort(value,n,i-1);

	if( i <= 0){
		
		classement = calloc(n, sizeof(int));

		if(classement == NULL){
			printf("Cannot create the table");
			exit(MALLOC_ERROR);
		}

		classement[0] = 0;

		return classement;
	}

	classement = sort(value, n, i-1);

	int j = 0;

	while( j < i && value[classement[j]] <= value[i] )
		j++;

	int tmp = i;

	while(j < i){

		classement[i] = classement[i-1];
		
		i--;
	}

	classement[j] = tmp;

	return classement;

}

Uint32 color(int r, int g, int b){

	return ((r<<8)+g << 8) +b;

}

void* interruption(void* arg){

	bool end = true;

	while(end){

		SDL_Event event;

		while(SDL_PollEvent(&event)){		//On attend un event

			switch(event.type){

				case SDL_QUIT:			//Si une demande d'interruption est levée
					end = false;
					break;

				default :
					break;
			}
		}
	}

	exit(INTERRUPTION_ERROR);

	return NULL;
}

void cleaning_thread(){

	pthread_t current = pthread_self();

	for(pthread_t i = 0; i <= 1024; i++)

		if(i != current)
			
			pthread_cancel(i);
}
