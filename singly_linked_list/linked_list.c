#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

void print_list(const node_t* head)
{
    const node_t* p = head;
    printf("Linked list : head -> ");
    while (p != NULL) { 
        printf("%d -> ", p->value);
        p = p->next;
    }  
    printf("NULL\n");
}

void destroy_list(node_t* head)
{
    node_t* p = head;
    while (p != NULL) {
        node_t* temp = p->next;
        free(p);
        p = NULL;
        p = temp;
    }
}

void add_front(node_t** phead, int value)
{
    node_t* new = (node_t*)malloc(sizeof(node_t));
    new->value = value;
    new->next = *phead;
    *phead = new;
}

void add_sorted(node_t** phead, int value)
{
    node_t** pp = phead;
    node_t* new = (node_t*)malloc(sizeof(node_t));
    new->value = value;
    while (*pp != NULL) {
        if ((*pp)->value > value) {
            break;
        }
        pp = &(*pp)->next;
    }
    new->next = *pp;
    *pp = new;
}

int remove_node(node_t** phead, int value)
{
    node_t** pp = phead;
    while (*pp != NULL) {
        if ((*pp)->value == value) {
            node_t* temp = *pp;
            *pp = (*pp)->next;
            free(temp);
            temp = NULL;
            goto success;
        }
        pp = &(*pp)->next;
    }
    return -1;
success:
    return 0;
}
