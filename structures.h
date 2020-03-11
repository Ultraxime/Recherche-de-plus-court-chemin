#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <stdbool.h>


typedef char** DrawableMap;

typedef bool** SimpleMap;

typedef struct Element Element;

struct Element{
	void* value;
	Element* next;
};

typedef Element* List;



#endif