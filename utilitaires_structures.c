#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "utilitaires_structures.h"

//Opérations sur les Element

Element* create_Element(void* value){

	Element* elt;

	elt = malloc(sizeof(Element));

	//l'Element n'a pu etre créé
	if(elt == NULL){
		printf("Error during creation of an Element\n");
		exit(-1);
	}

	//On initialise l'Element
	elt->value = value;
	elt->next = NULL;

	return elt;
}


//Operations sur les List

List create_List(){

	return NULL;
}

List push_List(Element* new, List list){

	//Si l'Element est une liste on ne peut le mettre en tête de List, il faut utiliser concatenate
	if(new->next != NULL){
		printf("New is not an Element but a List\n
			Use concatenate the next time\n");
		exit(-2);
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
		exit(-3);
	}

	if(*list == NULL){
		printf("You cannot pop Element from an empty List");
		exit(-4);
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