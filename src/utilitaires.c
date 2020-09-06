#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <getopt.h>
#include <stdint.h>

#include "structures.h"
#include "utilitaires.h"
#include "utilitaires_structures.h"
#include "errors.h"
#include "constantes.h"
#include "fonctions_genetiques.h"

/*
 ********************************************************
 * arg_parser(): Parse arguments 
 *	
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Parse the arguments gave at start
 *********************************************************
*/
void arg_parser(int argc, char** argv) {
    
    int32_t opt_val;

    while (true) {
	static struct option options[] = {
	    {"help", 		no_argument, 		0, 'h'},
	    {"nb-mutation", 	required_argument, 	0, 'm'}
	};
	opt_val = getopt_long(argc, argv, "hm:", options, NULL);

	// No more options
	if (opt_val == -1) {
	    break;
	}

	switch (opt_val) {
	    case 'h' :
		help(argv[0]);
		exit(0);
		break;
	    case 'm' :
		nb_generation = atoi(optarg);
		break;
	    default:
		help(argv[0]);
		exit(1);
		break;
	}
    }
}

/*
 ********************************************************
 * help(): Print the help
 *
 * @exe_name: Name of the executable
 *
 * Print the help of the software with options
 *********************************************************
*/
void help(char* exe_name) {
    printf("USAGE: %s [-h] [-m nb_mutatations]\n\n", exe_name);
    printf("Options:\n");
    printf("--help | -h : Print this help message\n");
    printf("--nb-mutation | -m <nb_mutatations> : Change the number of mutations. (Default : 100)\n");
}

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

int* sort(int* value, int n, int i){

	int* classement;

	if( i >= n ) return sort(value,n,i-1);

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
