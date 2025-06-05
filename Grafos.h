#ifndef Grafos_INCLUDED
#define MI_HEADER_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

#define GRAPH_ELEM int



typedef struct graphM
{
    int numvertices;
    Matrix* adyacencia;
    
}graphM;

graphM* graph_new(int vertices)
{
    graphM* newg=(graphM*)malloc(sizeof(graphM));
    if(newg)
    {
        newg->numvertices=vertices;
        newg->adyacencia=matrix_new(vertices,vertices);
    }
    return newg;
}

void graphM_set_adyacense(graphM* g)
{
    int row=matrix_rows(g->adyacencia);
    int col=matrix_columns(g->adyacencia);
}

#endif