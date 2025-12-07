#include "Grafo_Final.h"

GrafoM* graph_init(int vertices)
{
    GrafoM* result= (GrafoM*)malloc(sizeof(GrafoM));

    if(!result)
    {
        puts("No se puede reservar memoria");
        return NULL;
    }

    result->arista=matrix_new2(vertices,vertices);
    result->peso=matrix_new2(vertices,vertices);

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

Matrix* graph_get_matrix_adyacencia(GrafoM* g)
{
    return g->arista;
}

Matrix* graph_get_matrix_peso(GrafoM* g)
{
    return g->peso;
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



int graph_vertex_grade(GrafoM* g, int v) //Para saber el grado de un vertice hay que recorrer toda la fila, si se quiere
{                                       // saber todas las aristas se puede empezar desde la diagonal
    if(g==NULL) return -1;

    int count=0;

    if(!matrix_is_symmetric(g->arista))
    {
        puts("El grafo no es de tipo no dirigido");
        return -2;
    }else{
        int col=matrix_columns(g->arista);
        for(int i=0; i<col;i++)
        {
            if(matrix_get(g->arista,v,i)==1)
            {
                count++;
            }
        }
    }

    return count;
}

node* graph_list_vertex_adyacentes(GrafoM* g, int v)
{
    int col=matrix_columns(g->arista);

    node* result=NULL;

    for(int j=0; j<col; j++)
    {
        if(matrix_get(g->arista,v,j)==1)
        {
            node* temp=node_new(j);
            node_add_last1(&result,temp);
        }
    }

    return result;
}

vector* graph_count_vertex(GrafoM* g)
{
    if(g==NULL||g->arista==NULL||g->peso==NULL)return NULL;

    int dim=matrix_rows(g->arista);
    vector* result=vector_init(dim);

    if(result!=NULL)
    {
        int row=matrix_rows(g->arista);
        int col=matrix_columns(g->arista);
        int count = 0;
        for(int i=0; i<row;i++)
        {
            count = 0;
            for(int j=0;j<col;j++){
                if(matrix_get(g->arista,i,j)==1)
                {
                    count++;
                }
            }
            vector_add(result,count);
        }
    }

    return result;
}

int graph_cant_vertex(GrafoM*g)
{
    int result=matrix_rows(g->arista);
    return result;
}

int graph_cant_adyacencias(GrafoM* g, int vertex)
{
    int result=0;
    int dim=graph_cant_vertex(g);

    for(int i=0; i<dim;i++)
    {
        if(matrix_get(graph_get_matrix_adyacencia(g),vertex,i)==1)
        {
            result++;
        }
    }

    return result;
}

void graph_recorrido_amplitud(GrafoM* g, int vertex)
{
    int dim=graph_cant_vertex(g);
    vector* visitados=vector_init(dim);
    for (int u=0; u<dim;u++)
    {
        vector_add(visitados,0);
    }

    vector_set(visitados,vertex,1);

    queue* temp=queue_new(dim);
    enqueue(temp,vertex);

    while(!queue_isempty(temp))
    {
        int aux=dequeue(temp);
        for(int i=0; i<dim; i++)
        {
            if(matrix_get(graph_get_matrix_adyacencia(g),aux,i)==1 && vector_get(visitados,i)==0)
            {
                vector_set(visitados,i,1);
                enqueue(temp,i);
            }   
        }
        printf("%d->",aux+1);
    }
    vector_free(visitados);
    queue_free(temp);

}
//En los recorridos de grafps en profundidad se suele procesar el elemento antes de pushear el resto de vertices adyacentes
//Caso contra a amplitud que se procesa luego de meter.
void graph_recorrido_profundidad(GrafoM* g, int vertex)
{
    int dim=graph_cant_vertex(g);
    vector* visitados=vector_init(dim);
    for (int u=0; u<dim;u++)
    {
        vector_add(visitados,0);
    }

    vector_set(visitados,vertex,1);

    stack* temp=stack_new(dim);
    push(temp,vertex);

    while(!stack_isempty(temp))
    {
        int aux=pop(temp);
        printf("%d->",aux+1);
        for(int i=0; i<dim; i++)
        {
            if(matrix_get(graph_get_matrix_adyacencia(g),aux,i)==1 && vector_get(visitados,i)==0)
            {
                vector_set(visitados,i,1);
                push(temp,i);
            }   
        }

    }
    vector_free(visitados);
    stack_free(temp);

}

//Digrafo es un grafo dirigido en una sola orientación
int digraph_count_path(GrafoM* g, int src, int dst)
{
    
}