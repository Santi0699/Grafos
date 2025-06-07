#include "Listas.h"


node* node_new(t_elem_node data)
{
    node* r=(node*)malloc(sizeof(node));
    if(r!=NULL)
    {
        r->data=data;
        r->next=NULL;
    }

    return r;
}

t_elem_node node_free(node** a_node)
{
    node* aux= *a_node;
    t_elem_node data= 0;
    if(a_node!=NULL)
    {
        data= aux->data;
        *a_node = aux->next;
        free(aux);
    }
    return data;
}

void list_free(node** head)
{
    while(*head!=NULL)
    {
        t_elem_node e = node_free(head);
        // Aca deberia de ir una funcion que elimine el lo que contiene e si es que es otro tipo de dato distinto de int. Ej: fraccion o que contenga la direccion de memoria de un vector
    }
}

// imprimir un elemento entero
void int_print (int e){
    printf("%d ", e);
}

void list_print (node* a_node, void pnt(t_elem_node))
{
    while (a_node != NULL){
        pnt(a_node->data);
        a_node = a_node->next;
    }
}


node** list_search(node** head, t_elem_node e)
{
    while((*head)!=NULL && (*head)->data==e)
    {
        *head=(*head)->next;
    }
    
    return head;
}

node** node_find(node** head, t_elem_node e)
{
    while((*head)!=NULL && (*head)->data<e)
    {
        head=&(*head)->next;
    }
    
    return head;
}


node* node_add_first(node** head, node* new_node)
{
    if(new_node!=NULL)
    {
        new_node->next= *head;
        *head=new_node;
    }

    return new_node;
}

void node_add_first2(node** head, node* new_node)
{
    if(new_node!=NULL)
    {
        new_node->next= *head;
        *head=new_node;
    }
}

node* node_add_last(node** head, node* new_node)
{
    if(node_new!=NULL)
    {
        while((*head)!=NULL)
        {
            *head= (*head)->next;
        }

        (*head)->next=new_node;
    }
    return new_node;
}

void node_insert_in_order(node** head, node* new_node)
{
    if (new_node==NULL)return;

    if((*head)->next == NULL) (*head)->next=new_node;

    node* current=(*head);
    node* prev=NULL;

    while(current!=NULL && new_node->data < current->data)
    {
        prev=current;
        current=current->next;
    }

    if(new_node->data < current->data)
    {
        new_node->next=current;
        prev->next=new_node;
    }

    //return new_node;
}

void node_insert_in_order2(node** head, node* new_node)
{
    if (new_node == NULL) return;

    if (*head == NULL || new_node->data > (*head)->data) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    node* current = *head;
    while (current->next != NULL && current->next->data > new_node->data) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

node* node_insert_sort(node**h, node* new_node)
{
    if(new_node!=NULL)
    {
    node** aux = node_find(h, new_node->data);
    new_node->next = *aux;
    *aux = new_node;
    }
    
    return new_node;
}

node* node_remove_front(node** head)
{
    if(*head==NULL)return NULL;

    node* aux= (*head)->next;
    (*head)->next=NULL;
    node* remove= (*head);
    (*head)=aux;

    return remove;
}

node* delete_node(node** head, t_elem_node v)
{
    node** n = list_search(head,v);
    node* aux= *n;
    *n = aux->next;
    aux->next=NULL;

    return aux;

}

void delete_node2(node** head, t_elem_node v)
{
    node** n = list_search(head,v);
    node* aux= *n;
    *n = aux->next;
    aux->next=NULL;
    
    node_free(&aux);
}

//1.
int list_isorder(node* head)
{

    while(head->next!=NULL && head->data < head->next->data)
    {
        head=head->next;
    }
    
    if(head->next==NULL)
    {
        return 1;
    }
    return 0;
}
//2
void list_delete_same_value(node** head)
{
    if((*head)==NULL)return;
    node* aux = *head;
    while (aux!=NULL && aux->next!=NULL)
    {
        if((*head)->data==aux->next->data)
        {
            delete_node2(&aux->next,aux->next->data);
        }else{
            aux=aux->next;
        }
        
    }

    list_delete_same_value(&(*head)->next);
}
//3.
node* list_min_value(node* head)
{
    node* min=head;

    while(head!=NULL)
    {
        if(min->data < head->data)
        {
            min= head;
        }
        head=head->next;
    }

    return min;

}
//4.
node* list_create_reverse(node* head)// Si quiero agregar nodos de una lista para crear otra no debo hacerlo directamente con la funcion de add_first o add_last ya que modifico la original
{
    node* reverse_list=NULL; //No hace falta inicilizarlo ya que despues se pisa la informacion con la funcion de add_first
    while(head!=NULL)
    {
        node* new_node=node_new(head->data);//Para evitar lo de arriba genero un nodo nuevo con el valor actual del nodo head y lo agrego a la lista nueva revertida
        node_add_first2(&reverse_list,new_node);
        head=head->next;
    }

    return reverse_list;
    
}

//5

void list_invert(node** head)
{
    node* prev = NULL;
    node* current = *head;

    while (current != NULL)
    {
        node* next = current->next; 
        current->next = prev;       
        prev = current;             
        current = next;             
    }
    head=&prev; 
}

//6.

int is_pair(t_elem_node value)
{
    if(value%2 == 0)
    {
        return 1;
    }

    return 0;
}
//7.
void list_create_pair_impair(node** head, node** pair, node** impair)
{
    while((*head)!=NULL)
    {
        if(is_pair((*head)->data))
        {
            node* new_pair=node_new((*head)->data);
            node_add_first2(pair,new_pair);
        }else{
            node* new_impair=node_new((*head)->data);
            node_add_first2(impair,new_impair);
        }
        (*head)=(*head)->next;
    }
}

//8.

node* list_create_fusion_sorted(node** list1, node** list2) {
    node* result = NULL;

    while (*list1 != NULL) {
        node* temp = node_remove_front(list1);
        node_insert_in_order2(&result, temp);
    }

    while (*list2 != NULL) {
        node* temp = node_remove_front(list2);
        node_insert_in_order2(&result, temp);
    }

    return result;
}

//9.
int list_get_major_value(node* head)
{
    if(head==NULL)return 0;

    node* aux=head;
    int major=list_get_major_value(aux->next);

    if(major<aux->data) major=aux->data;

    return major;

}

t_elem_node list_prom(t_elem_node_t head)
{
    if(head==NULL) return 0;

    node* aux=head;
    t_elem_node sum=0;
    int i=0;
    t_elem_node prom=0;

    while(aux!=NULL)
    {
        sum=sum+aux->data;
        i++;
        aux=aux->next;
    }

    prom=sum/i;

    return prom;

}


node_t* list_get_major_prom(node_t* head)
{
    if(head==NULL)return NULL;

    node_t* aux=head;
    node_t* major=list_get_major_prom(aux->next);

    if(list_prom(major->data) < list_prom(aux->data) )
    {
        major=aux;
    }

    return major;

}

//Ejercicios practica Primer Parcial 
/*Objetivo: Dadas dos listas simplemente enlazadas que comparten algunos nodos (por dirección), eliminar los nodos compartidos de ambas listas sin liberar memoria.

Si un nodo aparece en ambas listas (mismo puntero), eliminarlo de ambas listas.

No modificar nodos únicos (solo compartidos).

No usar estructuras auxiliares.
*/


void delete_nodes(node** head, node* value)
{
    if(*head==NULL || value==NULL)return;

    if(*head==value)
    {
        *head=(*head)->next;
    }

    node* current= (*head);

    while(current->next!=NULL && current->next!=value)
    {
        current=current->next;
    }

    if(current->next==value)
    {
        current->next=value->next;
    }

}


void remove_shared_nodes(node** list_a, node** list_b)
{
    if(*list_a==NULL || *list_b==NULL) return;

    node* aux1= (*list_a);

    while(aux1!=NULL)
    {
        node* aux2=list_b;
        int delete=0;

        while (aux2!=NULL && delete==0)
        {
            if(aux1==aux2)
            {
                delete_nodes(list_a,aux1);
                delete_nodes(list_b,aux2);
                delete=1;
            }else{
                    aux2=aux2->next;
                 }
        }
        
        aux1=aux1->next;
    }

}

/*Objetivo: Intercambiar las colas (los últimos n nodos) entre dos listas simplemente enlazadas.

Las listas pueden tener distinta longitud.

Si alguna lista tiene menos de n elementos, no hacer nada.

No duplicar nodos, solo redirigir punteros.*/

int list_lenght(node* head)
{
    if(head==NULL)return 0;

    int i=0;

    node* current=head;

    while(current!=NULL)
    {
        current=current->next;
        i++;
    }

    return i;
}

void swap_tails(node** list_a, node** list_b, int n)
{
    if(*list_a==NULL|| *list_b==NULL) return;

    int size_list_a=list_lenght(*list_a);
    int size_list_b=list_lenght(*list_b);

    if(size_list_a<n || size_list_b<n) return;

    node* current= (*list_a);
    node* current2= (*list_b);
    node* aux1=NULL;
    node* aux2=NULL;

    for(int i=0; i<size_list_a-n;i++)
    {   
        aux1=current;
        current=current->next;
    }

    for(int j=0; j<size_list_b-n;j++)
    {
        aux2=current2;
        current2=current2->next;
    }

    if(aux1!=NULL)
    {
        aux1->next=current2;
    }else{
        *list_a = current2;
    }

    if(aux2!=NULL)
    {
        aux2->next=current;
    }else{
        *list_b=current;
    }

}
//esto detecta si apunta al anterior
int has_cycle2(node* list)
{
    if(list==NULL)return 0;
    if(list->next ==NULL) return 0;

    node* aux1=list;
    node* aux2=list->next;

    if(aux2->next==aux1) return 1;

    return has_cycle(aux1->next);

}

int has_cycle_rec(node* slow, node*fast)
{
    if(slow==NULL||fast==NULL)return 0;

    if(slow==fast) return 1;

    return has_cycle_rec(slow->next,fast->next->next);

}

int has_cycle(node* list)
{
    if(list==NULL||list->next==NULL)return 0;

    return has_cycle_recursive(list,list->next);
}

void add_last(node** head, t_elem_node_t value)
{
    while(*head!=NULL)
    {
        head= &(*head)->next;
    }

    *head= value;
}

int list_check_value(node* head,t_elem_node value)
{
    if(head==NULL) return 0;

    node* aux=head;
    int result=0;
    while(head!=NULL && head->data!=value)
    {
        aux=aux->next;
    }

    if(head->data==value)
    {
        result=1;
    }
    return result;
}