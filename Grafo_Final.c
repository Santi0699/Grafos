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

//--------------------------------Funciones vector de lista de adyacencias------------------------------------------------------//

GrafoVL* graphVL_init(int vertex)
{
    GrafoVL* result=(GrafoVL*)malloc(sizeof(GrafoVL));

    if(result==NULL) return NULL;

    result->adyacencia=vectorg_init(vertex);
    
    return result;
}

void graphVL_free(GrafoVL* g)
{
    vectorg_free(g->adyacencia);
    free(g);
}

vector_g* graphVL_get_vector_adyacencia(GrafoVL* g)
{
    return g->adyacencia;
}

void graphVL_add_vertex(GrafoVL* g,t_elem_node value)
{
    if(g==NULL)return ;

    vectorg_add(g->adyacencia,value);
}

void graphVL_add_adyacencia_no_dirigido(GrafoVL* g, int pos, t_vector_elem dst)
{
    node_add_last1(vectorg_get_head(graphVL_get_vector_adyacencia(g),pos),dst);
    node_add_last1(vectorg_get_head(graphVL_get_vector_adyacencia(g),dst),pos);
}

void graphVL_add_adyacencia_dirigido(GrafoVL* g, int pos, t_vector_elem dst)
{
    node_add_last1(vectorg_get_head(graphVL_get_vector_adyacencia(g),pos),dst);
}

//Digrafo es un grafo dirigido en una sola orientación
int digraph_count_path_acyclic(GrafoM* g, int src, int dst)
{
    int result=0;
    if(src==dst)
    {
        result=1;
    }else
        {
            node* aux=vector_get(graphVL_get_vector_adyacencia(g),src);
            while(!list_empty(aux))
            {
                result+=digraph_count_path(g,aux->data,dst);
                aux=aux->next;
            }
        }

    return result;
}

int digraph_count_path_cyclic(GrafoM* g, int* visitados, int src, int dst)
{
    if(src==dst)
    {
        return 1;
    }
    int result=0;
    visitados[src]=1;

    node* aux=vector_get(graphVL_get_vector_adyacencia(g),src);
    while(!list_empty(aux))
    {
        int value=aux->data;
        if(!visitados[value])
        {
            result+=digraph_count_path_cyclic(g,visitados,value,dst);
        }
        aux=aux->next;
    }
    return result;
}

void graphVL_print_all_path(GrafoVL* g, int src, int dst, int* visitados, vector* path, int index)
{
    vector_add(path,src);
    if(src==dst)
    {   
        vector_print2(path);
        vector_remove(path,vector_size(path)-1);
        return;
    }

    visitados[src]=1;

    node* aux=vector_get(graphVL_get_vector_adyacencia(g),src);
    while(!list_empty(aux))
    {
        int value=aux->data;
        if(!visitados[value])
        {
            graphVL_print_all_path(g,value,dst,visitados,path,index+1);
        }
        aux=aux->next;
    }

    visitados[src] = 0;
    vector_delete_last(path);

}

int graph_has_cycle(GrafoVL* g)
{
    int result = 0;
    int size=vectorg_size(g->adyacencia);
    int* visitados= calloc(sizeof(size),sizeof(int));

    int i=0;
    int flag=0;

    while(i<size && flag==0)
    {
        if(graph_has_cycle_t(g,visitados,i))
        {
            flag=1;
            result=1;
        }
        i++;
    }
 
    return result;
}

int graph_has_cycle_t(GrafoVL* g, int* visitados, int src)
{
    int flag=0;
    if(visitados[src]==1)
    {
        flag=1;
    }else{
        visitados[src]=1;
        node* aux=vectorg_get(graphVL_get_vector_adyacencia(g),src);

        while(aux!=NULL && flag==0)
        {
            if(!visitados[aux->data])
            {
                visitados[aux->data]=1;
                flag=graph_has_cycle_t(g,visitados,aux->data);
                visitados[aux->data]=0;
            }
            aux=aux->next;
        }

    }

    return flag;
}

int graph_is_a_star(GrafoVL* g)
{
    int result=0;
    vector_g* v=graphVL_get_vector_adyacencia(g);
    int v_size=vectorg_size(v);
    int root=0;
    int nodos=0;
    int pos=0;

    for (int i=0; i<v_size; i++)
    {
        node* temp= vectorg_get(v,i);
        int size=list_lenght(temp);
        if(size > 1 && size < v_size-1)
        {
            root++;
            pos=i;
        }else if(size==1)
            {
                nodos++;
            }
    }

    if(root!=1 && nodos != v_size - 1)
    {
        result=0;
    }

    if (result==1)
    {
        for(int j=0; j<v_size; j++)
        {
            if(j!=pos)
            {
                node* temp=vectorg_get(v,j);
                if(temp->data!=pos)
                {
                    result=0;
                }
            }
        }
    }

    return result;
}

