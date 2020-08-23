#ifndef UTILITAIRES_H_INCLUDED
#define UTILITAIRES_H_INCLUDED


#include "structures.h"

void arg_parser(int, char**);

bool init();

List facteurs_premiers(int);

void pause();

int* sort(int*, int, int);

#endif
