#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "structures.h"
#include "utilitaires.h"
#include "utilitaires_structures.h"
#include "errors.h"
#include "constantes.h"
#include "fonctions_genetiques.h"

bool verbose = false;

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
 
    static struct option options[] = {
	    {"help", 			no_argument, 		0, 'h'},
	    {"verbose",			no_argument,		0, 'v'},
	    {"nb-generation", 		required_argument, 	0, 'g'},
	    {"altitude", 		required_argument,	0, 'a'},
	    {"population-size", 	required_argument, 	0, 'p'},
	    {"mutation-probability",	required_argument,	0, 'm'}
	};
   int32_t opt_val = getopt_long(argc, argv, "hvg:a:p:m:", options, NULL);

    while (opt_val != -1) {

	switch (opt_val) {
	    case 'h' :
		help(argv[0]);
		exit(0);
		break;
	    case 'v' :
		verbose = true;
		break;
	    case 'g' :
		nb_generation = atoi(optarg);
		break;
	    case 'a':
		altitude = atoi(optarg);
		break;
	    case 'p':
		population_size = atoi(optarg);
		break;
	    case 'm':
		mutation_probability = atoi(optarg);
		break;
	    default:
		help(argv[0]);
		exit(1);
		break;
	}
	opt_val = getopt_long(argc, argv, "hvg:a:p:m:", options, NULL);
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
    printf(BOLD "\nUSAGE" COLOR_RESET ": %s [-h] [-g nb_mutations] [-a altitude] [-p population_size] [-m mutation_probability]\n\n", exe_name);
    puts(BOLD "Options" COLOR_RESET ":");
    puts(LONG_OPTION_COLOR "	--help" COLOR_RESET " | " SHORT_OPTION_COLOR "-h" COLOR_RESET " : Print this help message.");
    puts(LONG_OPTION_COLOR "	--verbose" COLOR_RESET " | " SHORT_OPTION_COLOR "-v" COLOR_RESET " : Print more information during the execution of the software.");
    puts(LONG_OPTION_COLOR "	--nb-generation" COLOR_RESET " | " SHORT_OPTION_COLOR "-g" COLOR_RESET " <nb_mutatations> : Change the number of generation. "
	    DEFAULT_VALUE_COLOR "(Default : 100)" COLOR_RESET);
    puts(LONG_OPTION_COLOR "	--altitude" COLOR_RESET " | " SHORT_OPTION_COLOR "-a" COLOR_RESET " <altitude> : Change the altitude. " 
	    DEFAULT_VALUE_COLOR "(Default : 127 - Max : 255)" COLOR_RESET);
    puts(LONG_OPTION_COLOR "	--population-size" COLOR_RESET " | " SHORT_OPTION_COLOR "-p" COLOR_RESET " <population_size> : Change the size of the population. " 
	    DEFAULT_VALUE_COLOR "(Default : 1000)" COLOR_RESET);
    puts(LONG_OPTION_COLOR "	--mutation-probability" COLOR_RESET " | " SHORT_OPTION_COLOR "-m" COLOR_RESET " <mutation_probability> : Change the probability of mutation " 
	    DEFAULT_VALUE_COLOR "(Default : 100000)" COLOR_RESET);
    puts("");	// Empty line between the end of the help and the shell line
}

List activeThread;

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
