#include "Grafo_Final.h"
//#include "Matrix.h"
//#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
//#include "Listas.h"

int main()
{
    GrafoM* g1=graph_init(5);
    matrix_print(g1->arista,print_int);

    graph_set_arista_no_dirigido(g1,0,1);
    graph_set_arista_no_dirigido(g1,0,2);
    graph_set_arista_no_dirigido(g1,1,0);
    graph_set_arista_no_dirigido(g1,1,3);
    graph_set_arista_no_dirigido(g1,2,0);
    graph_set_arista_no_dirigido(g1,2,4);
    graph_set_arista_no_dirigido(g1,3,1);
    graph_set_arista_no_dirigido(g1,3,4);
    graph_set_arista_no_dirigido(g1,4,2);    

    matrix_print(graph_get_matrix_adyacencia(g1),print_int);
    printf("\n");
    
    node* list=NULL;

    list=graph_list_vertex_adyacentes(g1,1);

    list_print(list, print_int);
    printf("\n");
    vector* adyacencias=graph_count_vertex(g1);

    vector_print2(adyacencias);
    printf("\n");
    graph_recorrido_amplitud(g1,0);
    printf("\n");
    graph_recorrido_profundidad(g1,0);
    return 0;
}