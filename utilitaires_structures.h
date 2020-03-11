#ifndef UILITAIRES_STRUCTURES_H_INCLUDED
#define UILITAIRES_STRUCTURES_H_INCLUDED

#include "structure.h"

//Operation sur les Element

Element* create_Element(void*);



//Operations sur les List

List create_List();

List push_List(Element*, List);

List concatenate_List(List, List);

List push_value_List(void*, List);

void* pop_List(List*);


#endif