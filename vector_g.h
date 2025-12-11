#ifndef VECTOR_G_H
#define VECTOR_G_H
#include <stdlib.h>
#include <stdio.h>
#include "Listas.h"
#define t_vector_elem node*
typedef struct _vector_g
{
    t_vector_elem* a;
    int size;
    int maxsize;
}vector_g;

vector_g* vectorg_init(int maxsize);

t_vector_elem vectorg_get(vector_g* v, int index);
t_vector_elem vectorg_get_head(vector_g* v, int index);
void vectorg_set(vector_g* v, int index, t_vector_elem value);
int vectorg_size(vector_g* v);
int vectorg_maxsize(vector_g* v);
int vector_isempty(vector_g* v);
int vectorg_isfull(vector_g* v);
void vectorg_add(vector_g* v, t_vector_elem value);
int vectorg_search(vector_g* v, t_vector_elem value);
t_vector_elem vectorg_remove(vector_g* v, t_vector_elem value);
void vectorg_free(vector_g* v);


#endif
