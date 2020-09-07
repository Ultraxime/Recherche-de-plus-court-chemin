#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "utilitaires_structures.h"
#include "errors.h"
#include "constantes.h"
#include "fonctions_graphes.h"


Graph graph_of_SimpleMap(SimpleMap map){

	Graph graph = create_Graph( N * M );

	for(uint16_t i = 0; i < N; i++){

		for(uint16_t j = 0; j < M; j++){

			if(!map[i][j]){
				if( i > 0 && !map[i-1][j]) add_arrete(&graph, i*N + j, (i-1)*N + j);
				if( j > 0 && !map[i][j-1]) add_arrete(&graph, i*N + j, i*N + j - 1);
				if( i < N-1 && !map[i+1][j]) add_arrete(&graph, i*N + j, (i+1)*N + j);
				if( i < M-1 && !map[i][j+1]) add_arrete(&graph, i*N + j, i*N + j + 1);
			}
		}
	}

	return graph;
}

Couple resultat_graphe_simple(SimpleMap map, Coordonnee coordonneeBegin, Coordonnee coordonneeEnd){

	uint16_t begin = coordonneeBegin.x * N + coordonneeBegin.y;
	uint16_t end = coordonneeEnd.x * N + coordonneeEnd.y;

	Graph graph = graph_of_SimpleMap(map);

	bool* mark;

	mark = calloc( graph.n, sizeof(bool));

	if(mark == NULL){
		printf("Cannot create mark table");
		exit(MALLOC_ERROR);
	}

	for(uint32_t i = 0; i < graph.n; i++)
		mark[i] = false;

	uint32_t* fathers;

	fathers = calloc( graph.n, sizeof(uint32_t));

	if( !fathers ){
		printf("Unable to allocate the memory for the fathers");
		exit(MALLOC_ERROR);
	}

	for(uint32_t i = 0; i < graph.n; i++)
		fathers[i] = -1;

	Queue queue = create_Queue();
}
