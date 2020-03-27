#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "fonctions_graphes.h"


Graph graph_of_SimpleMap(SimpleMap map){

	Graph graph = create_Graph( N * M );

	for(int i = 0; i < N; i++){

		for(int j = 0; j < M; j++){

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