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

	activeThread = create_List();

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    pthread_t interruptionT;

    uint8_t try = 255;

    while( pthread_create( &interruptionT, NULL, interruption, NULL) && try > 0 ){

    	printf("Faillure of the %d creation of thread\n", 255-try );
    	try --;
    }

    if( try == 0 ){
    	printf("Failed to start the thread for interruption");
    	exit(THREAD_ERROR);
    }else{
    	push_value_List( void_of_pthread(interruptionT), activeThread);
    }


    // make sure all thread are shut down before exit
    atexit(kill_all_threads);

	return true;    
}

List facteurs_premiers(uint16_t n){

	if(n <= 1)
		return create_List();

	uint16_t i = 2;

	while( n%i != 0 )
		i++;

	return push_value_List( void_of_int16(i), facteurs_premiers( n/i ));
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

uint32_t* sort(uint32_t* value, uint16_t n, uint16_t i){

	uint32_t* classement;

	if( i >= n ) return sort(value,n,i-1);

	if( i <= 0){
		
		classement = calloc(n, sizeof(uint32_t));

		if(classement == NULL){
			printf("Cannot create the table");
			exit(MALLOC_ERROR);
		}

		classement[0] = 0;

		return classement;
	}

	classement = sort(value, n, i-1);

	uint16_t j = 0;

	while( j < i && value[classement[j]] <= value[i] )
		j++;

	uint16_t tmp = i;

	while(j < i){

		classement[i] = classement[i-1];
		
		i--;
	}

	classement[j] = tmp;

	return classement;

}

Uint32 color(uint8_t r, uint8_t g, uint8_t b){

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

				case SDL_KEYDOWN:
					if( event.key.keysym.mod == KMOD_LCTRL || event.key.keysym.mod == KMOD_RCTRL )		//Si une touche CTRL est préssée
						if( event.key.keysym.sym == SDLK_c )										//Si la touche C est pressée
							end = false;
				default :
					break;
			}
		}
	}

	printf("Le programme c'est arrete sur demande de l'operateur\n");

	exit(INTERRUPTION_ERROR);

	pthread_exit(NULL);
}

void kill_all_threads(){

	while( !is_empty_List(activeThread) ){

		pthread_cancel( pthread_of_void( pop_List( &activeThread ) ) );
	}
}
