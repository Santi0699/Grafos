#ifndef VECTOR_H
#define VECTOR_H


#include <stdio.h>
#include <stdlib.h>
#define T_Elem Fraction
#define t_elem_vector int
typedef struct _vector{
    
    t_elem_vector* a; //array de T_Elem
    int size; //tam actual
    int maxsize; //tam maximo
}vector;

// Declaraciones de funciones
vector* vector_init(int max);
void vector_free(vector* v);
int vector_size(vector*v);
int vector_max_size(vector*v);
int vector_isfull(vector*v);
int vector_isempty(vector*v);
t_elem_vector vector_get(vector* v, int index);
void vector_set(vector* v, int index, t_elem_vector value);
void vector_add(vector* v, t_elem_vector value);
void vector_resize(vector** v);
void vector_remove(vector*v, int index);
void vector_print2(vector* v);
void vector_add_random2(vector* v);




#endif