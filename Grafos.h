#ifndef Grafos_INCLUDED
#define MI_HEADER_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"
#include "vector.h"
#include "Listas.h"
#include "queue_dynamic.h"
#include "stack_dynamic.h"

#define GRAPH_ELEM int


typedef struct graphM
{
    vector* vertex;
    Matrix* adyacencia;
    Matrix* cost;
    
}graphM;


graphM* graph_new(int vertices);
void graph_vertex_add(graphM* g, GRAPH_ELEM v);
void graphM_set_adjacency_dirigido(graphM* g,int destiny, int target);
void graphM_set_adjacency_no_dirigido(graphM* g,int destiny, int target);
void graph_edge_add_dirigido(graphM* g, int destiny, int target, int weight);
void graphM_edge_add_no_dirigido(graphM* g, int destiny, int target, int weight);
int graph_edge_weight(graphM* g, int v1, int v2);
GRAPH_ELEM graph_get(graphM*g, int index);
int graph_cmp(GRAPH_ELEM a, GRAPH_ELEM b);
int graph_vertex_index(graphM* g, GRAPH_ELEM vertex, int graph_cmp(GRAPH_ELEM,GRAPH_ELEM));
int graph_vertex_count(graphM* g);

#endif