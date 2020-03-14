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

	if(n = 0)
		return create_List();

	if(n = 1)
		return create_Element(void_of_int(1));

	int i = 2;

	while( n%i != 0 )
		i++;

	if(n/i == 1)
		return create_Element(void_of_int(n));
	
	else
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