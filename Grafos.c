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

int print_path_count(graph* g, int s, int t/*, int* visit*/)
{
    int r=0;
    if(s==t)
    {
        r=1;
    }else{  
        list* adj=graph_vertex_adjacent_list(g,s);
        while(!list_empty(adj))
        {
            int u=list_remove(adj);
            r+=print_path_count(g,u,t,/*visit*/);
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