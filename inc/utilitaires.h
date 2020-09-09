#ifndef UTILITAIRES_H_INCLUDED
#define UTILITAIRES_H_INCLUDED


#include <pthread.h>

#include "structures.h"

extern List activeThread;	//List qui contient les threads actifs et généraux

void arg_parser(int, char**);

void help(char*);

bool init();

List facteurs_premiers(uint16_t);

void pause();

uint32_t* sort(uint32_t*, uint16_t, uint16_t);

Uint32 color(uint8_t, uint8_t, uint8_t);

void* interruption(void*);

void kill_all_threads();

#endif
