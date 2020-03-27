#ifndef UTILITAIRES_STRUCTURES_H_INCLUDED
#define UTILITAIRES_STRUCTURES_H_INCLUDED

#include "structures.h"



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

int len_List(List);

void clear_List(List);

bool is_empty_List(List);



//Operations sur les SimpleMap

SimpleMap simpleMap_of_void(void*);

void clear_SimpleMap(SimpleMap, int);



//Operations sur les DrawableMap

DrawableMap drawableMap_of_void(void*);

void clear_DrawableMap(DrawableMap, int);



//Operations sur les LongMap

LongMap longMap_of_void(void*);

void clear_LongMap(LongMap, int);

unsigned long max_LongMap(LongMap, int, int);

unsigned long min_LongMap(LongMap, int, int);



//Operations sur les Coordonnee

Coordonnee create_Coordonnee(unsigned int, unsigned int);

Coordonnee random_Coordonnee(unsigned int, unsigned int);

bool is_equal_Coordonnee(Coordonnee, Coordonnee);

Coordonnee coordonnee_of_void(void*);

void* void_of_Coordonnee(Coordonnee);



//Operations sur les Individu

Individu create_Individu(unsigned int, unsigned int, unsigned int, unsigned int, unsigned char);

Individu random_Individu();



//Operations sur les Resultat

Resultat create_Resultat(Population, unsigned int *, List*);



//Operations sur les Couple

Couple create_Couple(void*, void*);



//Operations sur les Graph

Graph create_Graph(unsigned int);



//Operations sur les int

int int_of_void(void*);

void* void_of_int(int);



#endif
