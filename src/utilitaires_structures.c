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

	return *( (List*) &list);
}

List create_List(){

	return NULL;
}

List push_List(Element* new, List list){

	//Si l'Element est une liste on ne peut le mettre en tête de List, il faut utiliser concatenate
	if(new->next != NULL){
		printf("New is not an Element but a List\nUse concatenate the next time\n");
		exit(UNEXPECTED_VALUE_ERROR);
	}

	new->next = list;

	return new;
}

List concatenate_List(List list1, List list2){

	if(list1 == NULL)
		return list2;

	if(list1->next == NULL)
		push_List(list1, list2);

	else 
		concatenate_List(list1->next, list2);

	return list1;
}

List push_value_List(void* value, List list){

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
	*list = tmp->next;

	//On detruit en mémoire l'Element
	free(tmp);

	return result;
}

int len_List(List list){

	if(list == NULL)
		return 0;

	else
		return 1 + len_List(list->next);
}

void clear_List(List list){

	/*if(list == NULL)
		return;

	else{
		clear_List( list->next );
		free(list);
	}*/

	//J'ai été obligé ici de passer sur une ecriture non récursive car j'utilise des List trop grande pour la pile

	while(list != NULL){
		List next = list->next;


		free(list);

		list = next;
	}

}

bool is_empty_List(List list){

	return list == NULL;
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


//Operations sur les LongMap

LongMap longMap_of_void(void* map){

	return *( (LongMap*) &map );
}

void clear_LongMap(LongMap map, int n){

	for(int i = 0; i < n; i++)

		free(map[i]);

	free(map);
}

unsigned long max_LongMap(LongMap map, int n, int m){

	unsigned long max = map[0][0];

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(max < map[i][j])
				max = map[i][j];

	return max;

}

unsigned long min_LongMap(LongMap map, int n, int m){

	unsigned long min = map[0][0];

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(min > map[i][j])
				min = map[i][j];

	return min;

}


//Operations sur les Coordonnee

Coordonnee create_Coordonnee(unsigned int x, unsigned int y){
	
	Coordonnee coord;
	
	coord.x = x;
	coord.y = y;

	return coord;
}

Coordonnee random_Coordonnee(unsigned int n, unsigned int m){

	return create_Coordonnee( rand() % n, rand() % m);
}

bool is_equal_Coordonnee(Coordonnee coord1, Coordonnee coord2){

	return coord1.x == coord2.x && coord1.y == coord2.y;
}

Coordonnee coordonnee_of_void(void* coordonnee){

	return *( (Coordonnee*) &coordonnee );
}

void* void_of_Coordonnee(Coordonnee coordonnee){
	return *( (void**) &coordonnee );
}



//Operations sur les Individu

Individu create_Individu( unsigned int forward,
						  unsigned int right,
					 	  unsigned int backward,
						  unsigned int left,
						  unsigned char direction){

	Individu individu;

	unsigned int total = forward + right + backward + left;

	individu.forward = ( forward * 255 ) / total;
	individu.right = ( right * 255 ) / total;
	individu.backward = ( backward * 255 ) / total;
	individu.left = ( left * 255 ) / total;

	individu.direction = direction;
	
	return individu;
}

Individu random_Individu(){

	return create_Individu( rand() % 256,
							rand() % 256,
							rand() % 256,
							rand() % 256,
							rand() % 4);
}


//Operations sur les Resultat

Resultat create_Resultat(Population population,
						unsigned int* scores,
						List* chemins){

	Resultat resultat;

	resultat.population = population;
	resultat.scores = scores;
	resultat.chemins = chemins;

	return resultat;
}


//Operations sur les Couple

Couple create_Couple(void* key, void* value){

	Couple couple;

	couple.key = key;
	couple.value = value;

	return couple;
}



//Operations sur les Graph

Graph create_Graph(unsigned int n){

	Graph graph;

	graph.n = n;

	graph.arretes = calloc(n, sizeof(List));

	if(graph.arretes == NULL){
		printf("Cannot create the graph");
		exit(MALLOC_ERROR);
	}

	for(int i = 0; i < n; i++)
		graph.arretes[i] = create_List();

	return graph;
}

void add_arrete(Graph* graph, unsigned int i, unsigned int j){

	graph->arretes[i] = push_value_List(void_of_int(j), graph->arretes[i]);
}


//Operations sur les Queue

Queue create_Queue(){
	Queue queue;

	queue.exit = NULL;
	queue.entrance = NULL;

	return queue;
}

void push_Queue(Queue* queue, void* value){

	Element* new = create_Element(value);

	if(queue->exit == NULL){
		
		queue->exit == new;
		queue->entrance == new;
		
		return;

	}else{

		queue->entrance->next = new;
		queue->entrance = new;

		return;

	}
}

void* pop_Queue(Queue* queue){

	if(queue->exit == NULL){
		printf("Unable to pop an empty queue\n");
		exit(EMPTY_ERROR);
	}

	Element* exit = queue->exit;

	queue->exit = exit->next;

	if(exit->next == NULL)
		queue->entrance = NULL;

	void* result = exit->value;

	free(exit);

	return result;
}

bool is_empty_Queue(Queue queue){

	return queue.exit == NULL;
}



//Operations sur les int

int int_of_void(void* n){

	return *( (int*) &n );
}

void* void_of_int(int n){

	return *( (void**) &n );
}
