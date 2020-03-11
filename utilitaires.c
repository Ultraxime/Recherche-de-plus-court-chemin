#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "structures.h"
#include "utilitaires.h"
#include "errors.h"

bool init(){

	srand(time(NULL));					//Initialisation pour l'algorithme de random

	return true;    
}

