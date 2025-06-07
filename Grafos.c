#include "Grafos.h"

typedef struct _graph
{
    int* m;
    int count;
    int max;
    vector* vertex;
}graph;


graphM* graph_new(int vertices)
{
    graphM* newg=(graphM*)malloc(sizeof(graphM));
    if(newg)
    {
        newg->vertex=vector_init(vertices);
        newg->adyacencia=matrix_new(vertices,vertices);
    }
    return newg;
}

void graph_vertex_add(graphM* g, GRAPH_ELEM v)
{
    int i=vector_size(g->vertex);
    vector_add(g->vertex,v);
    int c= i+1;
    Matrix* aux=matrix_new(c,c);
    int row=matrix_rows(g->adyacencia);
    int col=matrix_columns(g->adyacencia);
    for(int k=0;k<row;k++)
    {
        for(int j=0;j<col;j++)
        {
            matrix_set(aux,k,j,matrix_get(g->adyacencia,k,j));
        }
    }
    free_matrix(g->adyacencia);
    g->adyacencia=aux;

}

void graphM_set_adjacency_dirigido(graphM* g,int destiny, int target)
{
    int row=matrix_rows(g->adyacencia);
    int col=matrix_columns(g->adyacencia);
    if(destiny<row && target<col) matrix_set(g->adyacencia,destiny,target,1);

}

void graphM_set_adjacency_no_dirigido(graphM* g,int destiny, int target)
{
    int row=matrix_rows(g->adyacencia);
    int col=matrix_columns(g->adyacencia);
    if(destiny<row && target<col) 
    {
        matrix_set(g->adyacencia,destiny,target,1);
        matrix_set(g->adyacencia,target,destiny,1);    
    }

}

void graph_edge_add_dirigido(graphM* g, int destiny, int target, int weight)
{
    int row=matrix_rows(g->adyacencia);
    int col=matrix_columns(g->adyacencia);
    if(destiny<row && target<col) matrix_set(g->adyacencia,destiny,target,weight);
}

void graphM_set_adjacency_no_dirigido(graphM* g, int destiny, int target, int weight)
{
    int row=matrix_rows(g->adyacencia);
    int col=matrix_columns(g->adyacencia);
    if(destiny<row && target<col) 
    {
        matrix_set(g->adyacencia,destiny,target,weight);
        matrix_set(g->adyacencia,target,destiny,weight);    
    }

}

int graph_edge_weight(graphM* g, int v1, int v2)
{
    return matrix_get(g->adyacencia,v1,v2);
}

GRAPH_ELEM graph_get(graphM*g, int index)
{
    return vector_get(g->vertex,index);
}

int graph_cmp(GRAPH_ELEM a, GRAPH_ELEM b)
{
    return a-b;
}

int graph_vertex_index(graphM* g, GRAPH_ELEM vertex, int graph_cmp(GRAPH_ELEM,GRAPH_ELEM))
{
    int size=vector_size(g->vertex);
    int i=0;
    while(i<size && graph_cmp(vector_get(g->vertex,i),vertex)!=0)
    {
        i++;
    }

    if(i>size)
    {
        i=-1;
    }
    return i;
}

int graph_vertex_count(graphM* g)
{
    return vector_size(g->vertex);
}


int graph_vertex_degree(graphM* g, int v)
{
    int degree=0;
    if(g!=NULL)
    {
            int row=matrix_columns(g->adyacencia);
            for(int i=0;i<row;i++)
            {
                if(matrix_get(g->adyacencia,v,i)==1)
                {
                    degree+=1;
                }
            }
    }
    return degree;
}


node* graph_vertex_adjacent_list(graphM* g, int v)
{
    node*l=NULL;
    int row=matrix_rows(g->adyacencia);
    for(int i=0;i<row;i++)
    {
        if(matrix_get(g->adyacencia,v,i)==1)
        {
            node_add_last(&l,node_new(vector_get((g->vertex),i)));
        }
    }
    return l;
}

#include <stdio.h>
#include <stdlib.h>

#define INF 999999 // Representa "infinito" (sin conexión)

void dijkstra(graphM* g, int origen, int* distancias) {
    int n = matrix_rows(g->adyacencia);
    int* visitado = calloc(n, sizeof(int));

    // Inicializamos las distancias
    for (int i = 0; i < n; i++) {
        distancias[i] = matrix_get(g->adyacencia, origen, i);
        if (distancias[i] == 0 && i != origen)
            distancias[i] = INF;
    }

    distancias[origen] = 0;
    visitado[origen] = 1;

    for (int k = 1; k < n; k++) {
        int min = INF;
        int u = -1;

        // Buscar el vértice no visitado con menor distancia
        for (int i = 0; i < n; i++) {
            if (!visitado[i] && distancias[i] < min) {
                min = distancias[i];
                u = i;
            }
        }

        if (u == -1) break; // No hay más alcanzables

        visitado[u] = 1;

        // Relajación: actualizar las distancias a los vecinos
        for (int v = 0; v < n; v++) {
            int peso = matrix_get(g->adyacencia, u, v);
            if (peso > 0 && !visitado[v] && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
            }
        }
    }

    free(visitado);
}

void dijkstra(graphM* g, int origen, int* distancias)
{
    int n = matrix_rows(g->adyacencia);
    int* visitado = calloc(n, sizeof(int));

    // Inicializamos las distancias
    for (int i = 0; i < n; i++) {
        distancias[i] = matrix_get(g->adyacencia, origen, i);
        if (distancias[i] == 0 && i != origen)
            distancias[i] = 99999;
    }

    distancias[origen] = 0;
    visitado[origen] = 1;

    for (int k = 1; k < n; k++) {
        int min = 99999;
        int u = -1;

        // Buscar el vértice no visitado con menor distancia
        for (int i = 0; i < n; i++) {
            if (!visitado[i] && distancias[i] < min) {
                min = distancias[i];
                u = i;
            }
        }

        if (u == -1) break; // No hay más alcanzables

        visitado[u] = 1;

        // Relajación: actualizar las distancias a los vecinos
        for (int v = 0; v < n; v++) {
            int peso = matrix_get(g->adyacencia, u, v);
            if (peso > 0 && !visitado[v] && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
            }
        }
    }

    free(visitado);
}

int graph_edge_cost(graphM* g, int v1, int v2)
{
    int result=-1;
    if(g!=NULL && g->cost!=NULL)
    {
        
        if(matrix_get(g->adyacencia,v1,v2)==1)
        {
            result=matrix_get(g->cost,v1,v2);
        }
    }

     return result;
}

int graph_edge_exists(graphM* g, int v1, int v2)
{
    return (g && g->adyacencia &&matrix_get(g->adyacencia,v1,v2)==1)?1:0;
}

vector* graph_vector_visitados(graphM* g)
{
    int n = vector_size(g->vertex);  // cantidad de vértices

    vector* visitados = (vector*)calloc(1, sizeof(vector));
    if (!visitados) return NULL;

    visitados->a = (t_elem_vector*)calloc(n, sizeof(t_elem_vector));  // todos en 0 (no visitado)
    visitados->size = n;
    visitados->maxsize = n;

    return visitados;
}

void print_BFS(graphM* g, int vertex)
{
    int size=vector_size(g->vertex);
    vector* visitados=vector_init(size);
    for(int i=0; i<size;i++)
    {
        vector_set(visitados,i,0);
    }
    vector_set(visitados,vertex,1);
    queue* q=queue_new(size*2);
    enqueue(q,vector_get(g->cost,0));

    while(!queue_isempty(q))
    {
        GRAPH_ELEM u=dequeue(q);
        node*l=graph_vertex_adjacent_list(g,u);
        while (l != NULL) {
            int adj = l->data;        
            if (vector_get(visitados, adj) == 0) {
                vector_set(visitados, adj, 1); 
                enqueue(q, adj);               
            }
            l = l->next;             
        }
    }
}

void print_dsf(graphM* g, int s, int t, int*visit, stack* p)
{
    push(p,s);
    visit[s]=1;
    if(s==t)
    {
        stack_print(s);
    }else{
        node* adj=graph_vertex_adjacent_list(g,s);
        while(adj!=NULL)
        {
            int u=node_remove_front(adj);
            if(visit[u]==0)
            {
                print_dsf(g,u,t,visit,p);
            }
        }
        node_free(adj);
    }
    pop(p);
    visit[s]=0;
}

/*
void print_dgf(graphM* g, int v, int* visitados)
{
    visitados[v]=1;
    printf("%d"graph_vertex_get(g,v));

    list* adj= graph_vertex_adjacent_list(g,v);

    while(!list_isempty(adj))
    {
        int u=list_remover(adj);
        if(visitados[v]==0)
        {
            print_dgf(g,u,visitados);
        }
    }
    list_free(&adj);
}
*/
int print_path_count(graph* g, int s, int t/*, int* visit*/)
{
    int r=0;
    if(s==t)
    {
        r=1;
    }else{  
        node* adj=graph_vertex_adjacent_list(g,s);
        while(!list_empty(adj))
        {
            int u=list_remove(adj);
            r+=print_path_count(g,u,t/*,visit*/);
            /*if(visit[v]==0)
                {
                    visit[u]=1;
                    r+=print_path_count(g,u,t,visit);
                    visit[u]=0;
                }
            */
        }
    }
    return r;
}
