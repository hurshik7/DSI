#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node {
    int value;
    struct node* next;
} node_t;

void print_list(const node_t* head);
void destroy_list(node_t* head);
void add_front(node_t** phead, int value);
void add_sorted(node_t** phead, int value);
int remove_node(node_t** phead, int value);

#endif /* LINKED_LIST_H */
