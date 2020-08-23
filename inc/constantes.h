#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#include <stdint.h>

#define H 127			//altitude de la plage sur 255

#define PUISSANCE 10 	//pas avec lequel on ajoute les cartes pour le bruit de Perlin

#define N 200

#define M 100

#define MUTATION 100000	//Probabilite de mutation

#define TAILLE 1000			//Taille d'une population

#define LIMITE 10*N*M 		//Longueur max d'un chemin

#define DEFAULT_NB_GENERATION 100	//Nombre de générations

/*  Color definitions */
#define ERROR_COLOR "\033[31m"
#define COLOR_RESET "\033[0m"

#endif
