#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <stdbool.h>


typedef unsigned char** DrawableMap;

typedef bool** SimpleMap;

typedef struct Element Element;

struct Element{
	void* value;
	Element* next;
};

typedef Element* List;

typedef unsigned long** LongMap;

typedef struct Coordonnee Coordonnee;

struct Coordonnee{
	unsigned int x;
	unsigned int y;
};

typedef struct Individu Individu;

struct Individu{
	unsigned char left;
	unsigned char right;
	unsigned char forward;
	unsigned char backward;

	unsigned char direction;
};

typedef Individu* Population;

typedef struct Resultat Resultat;

struct Resultat{
	Population population;
	unsigned int* scores;
	List* chemins;
};

typedef struct Couple Couple;

struct Couple{
	void* key;
	void* value;
};

#endif