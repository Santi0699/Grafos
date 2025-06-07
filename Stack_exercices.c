#include "stack_dynamic.h"
#include <stdio.h>
#include <stdlib.h>

void stack_add_random(stack* s, int cant_elem)
{
    
    for(int i=0; i<cant_elem;i++)
    {
        t_elem_stack value= rand() %10;
        push(s,value);
    }
}
//10.a
void stack_print(stack* s)
{
    if(stack_isempty(s)) return;

    stack* aux=stack_new(stack_getsize(s));

    while(!stack_isempty(s))
    {
        push(aux,pop(s));
        printf("|%d|\n",top(aux));
    }

    while(!stack_isempty(aux))
    {   
        push(s,pop(aux));
    }

    stack_free(aux);

}
//b.

void stack_print_recursive(stack* s)
{
    if(stack_isempty(s))return;

    t_elem_stack elem=pop(s);
//    printf("|%d|\n",elem); imprime la lista bien
    stack_print_recursive(s);
    printf("|%d|\n",elem); //imprime la lista invertida
    push(s,elem);
}

//12.a
int stack_sum_elements(stack* s)
{
    if(stack_isempty(s)) return 0;

    stack* aux=stack_new(stack_getsize(s));
    int sum=0;

    while(!stack_isempty(s))
    {
        push(aux,pop(s));
        sum=sum+top(aux);
    }

    while(!stack_isempty(aux))
    {   
        push(s,pop(aux));
    }

    stack_free(aux);

    return sum;
}
//14.
stack* stack_copy(stack*s)
{
    stack* aux= stack_new(stack_getsize(s));
    stack* result=stack_new(stack_getsize(s));
    while(!stack_isempty(s))
    {
        push(aux,pop(s));
    }

    while(!stack_isempty(aux))
    {
        t_elem_stack value=top(aux);
        push(result,value);
        push(s,pop(aux));
    }

    stack_free(aux);

    return result;
}


int stack_issort(stack*s)
{
    int sort=0;
    if(!stack_isempty(s))
    {
        int size_s=stack_getsize(s);
        stack* aux1=stack_new(size_s);
        push(aux1,pop(s));
        while(!stack_isempty(s)&&top(aux1)<top(s))
        {
            push(aux1,pop(s));
        }
        
        if(stack_isempty(s)) sort=1;

        while(!stack_isempty(aux1))
        {
            push(s,pop(aux1));
        }

        stack_free(aux1);
        
    }

    return sort;
    
}

void stack_insert_sort(stack* s, t_elem_stack value)
{
    if(!stack_isempty(s)||value>top(s))
    {
        push(s,value);
    }else
        {
            t_elem_stack temp=pop(s);
            stack_insert_sort(s,value);
            push(s,temp);
        }
}

void stack_sort(stack* s)
{
    if(!stack_isempty(s))
    {
        t_elem_stack value=pop(s);
        stack_sort(s);
        stack_insert_sort(s,value);
    }
}
