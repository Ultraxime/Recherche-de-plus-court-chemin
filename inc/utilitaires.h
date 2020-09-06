#ifndef UTILITAIRES_H_INCLUDED
#define UTILITAIRES_H_INCLUDED


#include <pthread.h>

#include "structures.h"

bool init();

List facteurs_premiers(int);

void pause();

int* sort(int*, int, int);

Uint32 color(int, int, int);

void* interruption(void*);

void cleaning_thread();

#endif
