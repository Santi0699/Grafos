#ifndef STACK_DYNAMIC_HEADER
#define MI_HEADER
#define t_elem_stack int

typedef struct _stack stack;


stack* stack_new(int maxsize);

void stack_free(stack* s);

int stack_getsize(stack* s);

int stack_getmaxsize(stack* s);

void push(stack* s, t_elem_stack elem);

t_elem_stack pop(stack* s);

t_elem_stack top(stack* s);

int stack_isempty(stack* s);

int stack_isfull(stack* s);

void stack_destroy(stack* s, void elem_free(t_elem_stack));
void stack_print(stack* s);
void stack_add_random(stack* s, int cant_elem);
void stack_print_recursive(stack* s);
int stack_sum_elements(stack* s);
stack* stack_copy(stack*s);
int stack_issort(stack*s);
void stack_insert_sort(stack* s, t_elem_stack value);
void stack_sort(stack* s);

#endif