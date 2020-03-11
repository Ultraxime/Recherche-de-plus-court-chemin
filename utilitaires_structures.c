#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "utilitaires_structures.h" 
#include "errors.h"

//Opérations sur les Element

Element element_of_void(void* elt){

	return *((Element*)&elt);
}

Element* create_Element(void* value){

	Element* elt;

	elt = malloc(sizeof(Element));

	//l'Element n'a pu etre créé
	if(elt == NULL){
		printf("Error during creation of an Element\n");
		exit(MALLOC_ERROR);
	}

	//On initialise l'Element
	elt->value = value;
	elt->next = NULL;

	return elt;
}


//Operations sur les List

List list_of_void(void* list){

	return *((list*)&list);
}

List create_List(){

	return NULL;
}

List push_List(Element* new, List list){

	//Si l'Element est une liste on ne peut le mettre en tête de List, il faut utiliser concatenate
	if(new->next != NULL){
		printf("New is not an Element but a List\n
			Use concatenate the next time\n");
		exit(UNEXPECTED_VALUE_ERROR);
	}

	new->next = list;

	return new;
}

List concatenate_List(List list1, List list2){

	if(list1 == NULL)
		return list2;

	if(list1->next == NULL)
		push(list1, list2);

	else 
		concatenate(list1->suivant, list2);

	return list1;
}

List push_Value_List(void* value, List list){

	Element* elt = create_Element(value);

	return push_List(elt, list);
}

void* pop_List(List* list){

	if(list == NULL){
		printf("The List does not exist\n");
		exit(NULL_ERROR);
	}

	if(*list == NULL){
		printf("You cannot pop Element from an empty List");
		exit(EMPTY_ERROR);
	}

	//On récupére la valeur du résultat
	void* result = (*list)->value;

	//On retient temporairement en memoire le pointeur vers l'Element à détruire
	Element* tmp = (*list);

	//On change la List vers laquelle pointe notre pointeur
	list = tmp->next;

	//On detruit en mémoire l'Element
	free(tmp);

	return result;
}


//Operations sur les SimpleMap

SimpleMap simpleMap_of_void(void* map){

	return *((SimpleMap*)&map);
}

void clear_SimpleMap(SimpleMap map, int n){

	for(int i = 0; i<n; i++)
		free(map[i]);

	free(map);
}


//Operations sur les DrawableMap

DrawableMap drawableMap_of_void(void* map){

	return *((DrawableMap*)&map);
}

void clear_DrawableMap(DrawableMap map, int n){

	for(int i = 0; i<n; i++)
		free(map[i]);

	free(map);
}