#ifndef Grafo_Final_INCLUDED
#define MI_HEADER_INCLUDED
#include "Listas.h"
#include "vector.h"
#include "queue_dynamic.h"
#include "stack_dynamic.h"
#include "Matrix.h"
#include "vector_g.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct _GrafoM
{
    Matrix* arista;
    Matrix* peso;
}GrafoM;

typedef struct _GrafoVL
{
    vector_g* adyacencia;
}GrafoVL;


GrafoM* graph_init(int vertices);
void graph_set_arista_no_dirigido(GrafoM* g, int src, int dst);
void graph_set_arista_dirigido(GrafoM* g, int src, int dst);
void graph_set_peso_dirigido(GrafoM* g, int src, int dst, int peso);
void graph_set_peso_no_dirigido(GrafoM* g, int src, int dst, int peso);
t_elem_matrix graph_get_peso(GrafoM* g, int src, int dst);
void graph_delete_arista_no_dirigido(GrafoM* g, int src,int dst);
void graph_delete_arista_dirigido(GrafoM* g, int src,int dst);
void graph_delete(GrafoM* g);
int graph_check_arista(GrafoM*g, int src, int dst);
void graph_delete_vertex(GrafoM* g, int vertex);
void graph_add_vertex(GrafoM* g, int vertex);
Matrix* graph_get_matrix_adyacencia(GrafoM* g);
Matrix* graph_get_matrix_peso(GrafoM* g);
int graph_vertex_grade(GrafoM* g, int v);
node* graph_list_vertex_adyacentes(GrafoM* g, int v);
vector* graph_count_vertex(GrafoM*g);
int graph_cant_vertex(GrafoM*g);
int graph_cant_adyacencias(GrafoM* g, int vertex);
void graph_recorrido_amplitud(GrafoM* g, int vertex);
void graph_recorrido_profundidad(GrafoM* g, int vertex);

vector_g* graphVL_get_vector_adyacencia(GrafoVL* g);

#endif


