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

uint32_t len_List(List);

void clear_List(List);

bool is_empty_List(List);



//Operations sur les SimpleMap

SimpleMap simpleMap_of_void(void*);

void clear_SimpleMap(SimpleMap, uint16_t);



//Operations sur les DrawableMap

DrawableMap drawableMap_of_void(void*);

void clear_DrawableMap(DrawableMap, uint16_t);



//Operations sur les LongMap

LongMap longMap_of_void(void*);

void clear_LongMap(LongMap, uint16_t);

uint64_t max_LongMap(LongMap, uint16_t, uint16_t);

uint64_t min_LongMap(LongMap, uint16_t, uint16_t);



//Operations sur les Coordonnee

Coordonnee create_Coordonnee(uint16_t, uint16_t);

Coordonnee random_Coordonnee(uint16_t, uint16_t);

bool is_equal_Coordonnee(Coordonnee, Coordonnee);

Coordonnee coordonnee_of_void(void*);

void* void_of_Coordonnee(Coordonnee);



//Operations sur les Individu

Individu create_Individu(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t);

Individu random_Individu();



//Operations sur les Resultat

Resultat create_Resultat(Population, uint32_t*, List*);



//Operations sur les Couple

Couple create_Couple(void*, void*);



//Operations sur les Graph

Graph create_Graph(uint32_t);

void add_arrete(Graph*, uint32_t, uint32_t);



//Operations sur les Queue

Queue create_Queue();

void push_Queue(Queue*, void*);

void* pop_Queue(Queue*);

bool is_empty_Queue(Queue);



//Operations sur les int

uint16_t int16_of_void(void*);

uint32_t int32_of_void(void*);

void* void_of_int16(uint16_t);

void* void_of_int32(uint32_t);


#endif
