#include "Grafo_Final.h"
//#include "Matrix.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
//#include "Listas.h"

int main()
{
    GrafoM* g1=graph_init(3);
    matrix_print(g1->arista,print_int);

    graph_set_arista_no_dirigido(g1,0,1);
    graph_set_arista_no_dirigido(g1,2,1);
    graph_set_arista_no_dirigido(g1,0,2);

    matrix_print(graph_get_matrix_adyacencia(g1),print_int);
    printf("rows=%d, cols=%d\n", g1->arista->row, g1->arista->col);
    
    node* list=NULL;
//    node_add_last1(&list,node_new(3));
//    node_add_last1(&list,node_new(4));
//    node_add_last1(&list,node_new(5));
//    node_add_last1(&list,node_new(6));
//    list_print(list,print_int);
    list=graph_list_vertex_adyacentes(g1,1);
//    list_print(list,print_int);
    if (list == NULL)
    puts("La lista vino vacia");
else
    list_print(list, print_int);

    return 0;
}