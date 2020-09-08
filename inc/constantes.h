#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#include <stdint.h>

#define DEFAULT_ALTITUDE 127

#define PUISSANCE 10 	//pas avec lequel on ajoute les cartes pour le bruit de Perlin

#define N 200

#define M 100

#define DEFAULT_MUTATION_PROBABILITY 100000	

#define DEFAULT_POP_SIZE 1000			

#define LIMITE 10*N*M 		//Longueur max d'un chemin

#define DEFAULT_NB_GENERATION 100	// Default generation number. Can be change with arguments at execution

/*  Color definitions */
#define ERROR_COLOR "\033[31m"
#define COLOR_RESET "\033[0m"
#define SHORT_OPTION_COLOR "\033[94m"
#define LONG_OPTION_COLOR "\033[92m"
#define DEFAULT_VALUE_COLOR "\033[90m"

extern uint32_t mutation_probability; 	//Probabilite de mutation
extern uint16_t population_size;	//Taille d'une population
extern uint8_t altitude;		//altitude de la plage sur 255
extern uint16_t nb_generation;
#endif
