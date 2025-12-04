#include "Grafo_Final.h"

GrafoM* graph_init(int vertices)
{
    GrafoM* result= (GrafoM*)malloc(sizeof(GrafoM));

    if(!result)
    {
        puts("No se puede reservar memoria");
        return NULL;
    }

    result->arista=matrix_new(vertices,vertices);
    result->peso=matrix_new(vertices,vertices);

    return result;

}

void graph_set_arista_no_dirigido(GrafoM* g, int src, int dst)
{
    matrix_set(g->arista,src,dst,1);
    matrix_set(g->arista,dst,src,1);

}

void graph_set_arista_dirigido(GrafoM* g, int src, int dst)
{
    matrix_set(g->arista,src,dst,1);

}

void graph_set_peso_dirigido(GrafoM* g, int src, int dst, int peso)
{
    matrix_set(g->peso,src,dst,peso);
}


void graph_set_peso_no_dirigido(GrafoM* g, int src, int dst, int peso)
{
    matrix_set(g->peso,src,dst,peso);
    matrix_set(g->peso,dst,src,peso);
}

t_elem_matrix graph_get_peso(GrafoM* g, int src, int dst)
{
    return (matrix_get(g->peso,src,dst)==0)?-1:matrix_get(g->peso,src,dst);
}

void graph_delete_arista_no_dirigido(GrafoM* g, int src,int dst)
{
    matrix_set(g->arista,src,dst,0);
    matrix_set(g->arista,dst,src,0);
}

void graph_delete_arista_dirigido(GrafoM* g, int src,int dst)
{
    matrix_set(g->arista,src,dst,0);
}

void graph_delete(GrafoM* g)
{
    free_matrix(g->arista);
    free_matrix(g->peso);
    free(g);
}

int graph_check_arista(GrafoM*g, int src, int dst)
{
    return (matrix_get(g->arista,src,dst)==1)?1:0;
}

void graph_delete_vertex(GrafoM* g, int vertex)
{
    matrix_delete_row(g->arista,vertex);
    matrix_delete_col(g->arista,vertex);
}

void graph_add_vertex(GrafoM* g, int vertex)
{
    matrix_rezise(g->arista, vertex);
}