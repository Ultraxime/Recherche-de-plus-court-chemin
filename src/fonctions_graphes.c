#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "utilitaires_structures.h"
#include "errors.h"
#include "constantes.h"
#include "fonctions_graphes.h"


Graph graph_of_SimpleMap(SimpleMap map){

	Graph graph = create_Graph( map_width * map_height );

	for (uint16_t i = 0; i < map_width; i++) {

		for (uint16_t j = 0; j < map_height; j++) {

			if (!map[i][j]) {
				if( i > 0 && !map[i-1][j]) add_arrete(&graph, i*map_width + j, (i-1)*map_width + j);
				if( j > 0 && !map[i][j-1]) add_arrete(&graph, i*map_width + j, i*map_width + j - 1);
				if( i < map_width-1 && !map[i+1][j]) add_arrete(&graph, i*map_width + j, (i+1)*map_width + j);
				if( i < map_height-1 && !map[i][j+1]) add_arrete(&graph, i*map_width + j, i*map_width + j + 1);
			}
		}
	}

	return graph;
}

Couple resultat_graphe_simple(SimpleMap map, Coordonnee coordonneeBegin, Coordonnee coordonneeEnd){

	unsigned int begin = coordonneeBegin.x * map_width + coordonneeBegin.y;
	unsigned int end = coordonneeEnd.x * map_width + coordonneeEnd.y;

	Graph graph = graph_of_SimpleMap(map);

	bool* mark;

	mark = malloc( graph.n * sizeof(bool));

	if(mark == NULL){
		printf("Cannot create mark table");
		exit(MALLOC_ERROR);
	}

	for(int i = 0; i < graph.n; i++)
		mark[i] = false;

	int* fathers;

	fathers = malloc( graph.n * sizeof(int));

	for(int i = 0; i < graph.n; i++)
		fathers[i] = -1;

	Queue queue = create_Queue();
}
