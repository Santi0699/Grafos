#ifndef Grafos_INCLUDED
#define MI_HEADER_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"
#include "vector.h"
#include "Listas.h"

#define GRAPH_ELEM int


typedef struct graphM
{
    vector* vertex;
    Matrix* adyacencia;
    Matrix* cost;
    
}graphM;

void graphM_set_adyacense_dirigido(graphM* g,int destiny, int target);
void graphM_set_adyacense_no_dirigido(graphM* g,int destiny, int target);

#endif