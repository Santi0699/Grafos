#include "vector_g.h"

vector_g* vectorg_init(int maxsize)
{
    vector_g* result=(vector_g*)malloc(sizeof(vector_g));

    if (result==NULL) return NULL;

    result->a=(t_vector_elem*)malloc(maxsize*sizeof(t_vector_elem));
    result->size=0;
    result->maxsize=maxsize;

    return result;
}

t_vector_elem vectorg_get(vector_g* v, int index)
{
    return v->a[index];
}

t_vector_elem vectorg_get_head(vector_g* v, int index)
{
    return &v->a[index];
}

void vectorg_set(vector_g* v, int index, t_vector_elem value)
{
    if(value==NULL)
    {
        puts("El elemento esta vacio");
        return;
    }
    v->a[index]=value;
}

int vectorg_size(vector_g* v)
{
    return v->size;
}


int vectorg_maxsize(vector_g* v)
{
    return v->maxsize;
}

int vector_isempty(vector_g* v)
{
    int result=1;

    if(v->size!=0)
    {
        result=0;
    }
    
    return result;
}


int vectorg_isfull(vector_g* v)
{
    int result=0;

    if(v->size==v->maxsize)
    {
        result=1;
    }
    
    return result;
}

void vectorg_add(vector_g* v, t_vector_elem value)
{
    if(v==NULL)return;

    if(vector_isempty(v))
    {
        v->a[v->size]=value;
        v->size++;
    }else
        {
            v->a = (t_vector_elem*)realloc(v->a,  sizeof(v->a) + (v->maxsize + 1) * sizeof(t_vector_elem));
            v->maxsize = v->maxsize + 1;
            v->a[v->size] = (t_vector_elem)value;
            v->size = v->size + 1;
        }
}

int vectorg_search(vector_g* v, t_vector_elem value)
{
    int i=0;
    int find=0;
    while( find==0 && i<v->maxsize )
    {
        if(v->a[i]==value)
        {
            find=1;
        }else{
            i++;
        }
    }
    return i;
}

t_vector_elem vectorg_remove(vector_g* v, t_vector_elem value)
{
    if(v==NULL)return ;
    int pos=vectorg_search(v,value);
    t_elem_node result= vectorg_get(v,pos);

    for(int i = pos; i < v->size - 1; i++)
    {
        v->a[i] = v->a[i + 1];
    }

    v->size--;

    return result;
}

void vectorg_free(vector_g* v)
{
    int dim=v->size;
    for(int i=0;i<dim; i++)
    {
        list_free(&v->a[i]);
    }
    free(v->a);
    free(v);
}



