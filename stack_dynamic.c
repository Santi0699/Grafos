#include <stdio.h>
#include <stdlib.h>

#include "stack_dynamic.h"

typedef struct _stack_node {
  t_elem_stack value;
  struct _stack_node *next;
} stack_node;

typedef struct _stack {
  stack_node *head;
  int maxsize;
  int count;
} stack;

stack* stack_new(int maxsize) {
  stack* s = (stack*) malloc(sizeof(stack));

  s->head = NULL;
  s->maxsize = maxsize;
  s->count = 0;

  return s;
}

void stack_free(stack* s) {
  stack_node *aux;

  while (s->head != NULL) {
    aux = s->head;
    s->head = s->head->next;
    free(aux);
  }

  free(s);
}

int stack_getsize(stack* s) {
  return s->count;
}

int stack_getmaxsize(stack* s) {
  return s->maxsize;
}

int stack_isempty(stack* s) {
  return (s->count == 0);
}

int stack_isfull(stack* s) {
  return (s->count == s->maxsize);
}

void push(stack* s, t_elem_stack elem) {
  if (stack_isfull(s)) {
    printf("Stack overflow\n");
    exit(1);
  }
  
  stack_node *new_node = (stack_node*) malloc(sizeof(stack_node));

  new_node->value = elem;
  new_node->next = s->head;

  s->head = new_node;
  s->count++;
}

t_elem_stack pop(stack* s) {
  if (stack_isempty(s)) {
    printf("Stack underflow\n");
    exit(1);
  }

  stack_node *aux = s->head;
  t_elem_stack elem = s->head->value;

  s->head = s->head->next;
  s->count--;

  free(aux);

  return elem;
}

t_elem_stack top(stack* s) {
  if (stack_isempty(s)) {
    printf("Stack underflow\n");
    exit(1);
  }

  return s->head->value;
}

void stack_destroy(stack* s, void elem_free(t_elem_stack)){
  while (!stack_isempty(s)){
    elem_free(pop(s));
  }
}