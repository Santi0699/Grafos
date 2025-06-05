#ifndef Matrix_H
#define MI_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#define t_elem_matrix int

typedef struct _Matrix
{
    t_elem_matrix** a;
    int col;
    int row;
}Matrix;



typedef struct _vector vector;
typedef struct _Matrix Matrix;
Matrix* matrix_new(int row, int col);
void free_matrix(Matrix* m);
int matrix_rows(Matrix* m);
int matrix_columns(Matrix* m);
t_elem_matrix matrix_get(Matrix* m, int row, int col);
void matrix_set (Matrix* m, int row, int col, t_elem_matrix value);
void matrix_print(Matrix* m, void (*print)(t_elem_matrix));
void matrix_add_random(Matrix* m);
void print_int(t_elem_matrix x);
void matrix_change_row_with_vector(Matrix* m, vector* v,int row_change);
void matrix_change_col_with_vector(Matrix* m, vector* v,int col_change);
Matrix* matrix_sum(Matrix* m1, Matrix* m2);
Matrix* matrix_sum_vector(Matrix* m1, vector* v);
Matrix* matrix_mult(Matrix* m1, Matrix* m2);
t_elem_matrix matrix_determinant_recursive(Matrix* m);
int matrix_is_symmetric(Matrix* m);

#endif