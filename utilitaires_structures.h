#ifndef UILITAIRES_STRUCTURES_H_INCLUDED
#define UILITAIRES_STRUCTURES_H_INCLUDED

#include "structure.h"

//Operation sur les Element

Element element_of_void(void*);

Element* create_Element(void*);



//Operations sur les List

List list_of_void(void*);

List create_List();

List push_List(Element*, List);

List concatenate_List(List, List);

List push_value_List(void*, List);

void* pop_List(List*); 


//Operations sur les SimpleMap

SimpleMap simpleMap_of_void(void*);

void clear_SimpleMap(SimpleMap, int);


//Operations sur les DrawableMap

DrawableMap drawableMap_of_void(void*);

void clear_DrawableMap(DrawableMap, int);

#endif