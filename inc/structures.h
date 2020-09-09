#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#include <pthread.h>


typedef uint8_t** DrawableMap;

typedef Uint32* Screen;

typedef bool** SimpleMap;

typedef struct Element Element;

struct Element{
	void* value;
	Element* next;
};

typedef Element* List;

typedef uint64_t** LongMap;

typedef struct Coordonnee Coordonnee;

struct Coordonnee{
	uint16_t x;
	uint16_t y;
};

typedef struct Individu Individu;

struct Individu{
	uint8_t left;
	uint8_t right;
	uint8_t forward;
	uint8_t backward;

	uint8_t direction;
};

typedef Individu* Population;

typedef struct Resultat Resultat;

struct Resultat{
	Population population;
	uint32_t* scores;
	List* chemins;
};

typedef struct Couple Couple;

struct Couple{
	void* key;
	void* value;
};

typedef struct Graph Graph;

struct Graph{
	uint32_t n;
	List* arretes;
};

typedef struct Queue Queue;

struct Queue{
	List exit;
	Element* entrance;	
};

#endif
