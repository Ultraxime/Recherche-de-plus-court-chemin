#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <stdbool.h>


typedef (unsigned char)** DrawableMap;

typedef bool** SimpleMap;

typedef struct Element Element;

struct Element{
	void* value;
	Element* next;
};

typedef Element* List;

typedef (unsigned long)** LongMap;

typedef struct Coordonnee Coordonnee;

struct Coordonnee{
	unsigned int x;
	unsigned int y;
};

#endif