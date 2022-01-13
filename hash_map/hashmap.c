#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{
    size_t i;
    hashmap_t* ret_hashmap;
    ret_hashmap = malloc(1 * sizeof(hashmap_t));
    ret_hashmap->length = length;
    ret_hashmap->plist = malloc(length * sizeof(node_t*));
    for (i = 0; i < length; ++i) {
        ret_hashmap->plist[i] = NULL;
    }
    ret_hashmap->hash_func = p_hash_func;
    return ret_hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    node_t* new_node;
    node_t* node_ptr;
    char mode = 'd';
    size_t index = hashmap->hash_func(key) % hashmap->length;
    if (hashmap->plist[index] != NULL) {
        mode = 'i';
        node_ptr = hashmap->plist[index];
        if (strcmp(key, node_ptr->key) == 0) {
            return FALSE;
        }
        while (node_ptr->next != NULL) {
            node_ptr = node_ptr->next;
            if (strcmp(key, node_ptr->key) == 0) {
                return FALSE;
            }
        }
    }

    new_node = malloc(1 * sizeof(node_t));
    new_node->key = malloc(strlen(key) + 1);
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = NULL;

    switch (mode) {
    case 'd':
        hashmap->plist[index] = new_node;
        break;
    case 'i':
        node_ptr->next = new_node;
        break;
    default:
        break;
    }
    return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    node_t* node_ptr;
    size_t index = hashmap->hash_func(key) % hashmap->length;   
    if (hashmap->plist[index] == NULL) {
        return -1;
    }    
    node_ptr = hashmap->plist[index];
    while (node_ptr != NULL) {
        if (strcmp(node_ptr->key, key) == 0) {
            return node_ptr->value;
        }
        node_ptr = node_ptr->next;
    }
    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    node_t* node_ptr;
    size_t index = hashmap->hash_func(key) % hashmap->length;    
    if (hashmap->plist[index] == NULL) {
        return FALSE;
    }    
    node_ptr = hashmap->plist[index];
    while (node_ptr != NULL) {
        if (strcmp(node_ptr->key, key) == 0) {
            node_ptr->value = value;
            return TRUE;
        }
        node_ptr = node_ptr->next;
    }
    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    node_t* node_ptr;
    node_t* temp_ptr;
    size_t index = hashmap->hash_func(key) % hashmap->length;    
    if (hashmap->plist[index] == NULL) {
        return FALSE;
    }    
    node_ptr = hashmap->plist[index];
    if (strcmp(node_ptr->key, key) == 0) {
        hashmap->plist[index] = node_ptr->next;
        free(node_ptr->key);
        node_ptr->key = NULL;
        free(node_ptr);
        return TRUE;
    }
    while (node_ptr->next != NULL) {
        temp_ptr = node_ptr;
        node_ptr = node_ptr->next;
        if (strcmp(node_ptr->key, key) == 0) {
            temp_ptr->next = node_ptr->next;
            free(node_ptr->key);
            node_ptr->key = NULL;
            free(node_ptr);
            return TRUE;
        }
    }
    return FALSE; 
}

void destroy(hashmap_t* hashmap)
{
    size_t i;
    node_t* node_ptr;
    for (i = 0; i < hashmap->length; ++i) {
        if (hashmap->plist[i] != NULL) {
            node_ptr = hashmap->plist[i];
            while (node_ptr != NULL) {
                node_t* next_ptr = node_ptr->next;
                free(node_ptr->key);
                node_ptr->key = NULL;
                free(node_ptr);
                node_ptr = next_ptr;
            }
            hashmap->plist[i] = NULL;
        }
    }
    free(hashmap->plist);
    hashmap->plist = NULL;
    free(hashmap);
    hashmap = NULL;
}
