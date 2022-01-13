#include "../hash.h"
#include <limits.h>
#include <stdio.h>

void init_hash_map(hash_map_t* hm)
{
    size_t i;
    hm->count = 0;
    for (i = 0; i < BUCKET_SIZE; i++) {
        hm->hash_map[i] = INT_MIN;
    }
}

int has_value(const hash_map_t* hm, int value)
{
    if (hm->count == 0) {
        return FALSE;
    }

    int index = value % BUCKET_SIZE;
    if (index < 0) {
        index += BUCKET_SIZE;
    }

    int start = index;

    do {
        if (hm->hash_map[index] == value) {
            return TRUE;
        } else if (hm->hash_map[index] == INT_MIN) {
            return FALSE;
        }
        
        index = (index + 1) % BUCKET_SIZE;

    } while (index != start);

    return FALSE; 
}

int add(hash_map_t* hm, int value)
{
    if (hm->count == BUCKET_SIZE) {
        return FALSE;
    }

    int index = value % BUCKET_SIZE;
    if (index < 0) {
        index += BUCKET_SIZE;
    }

    int start = index;

    do {
        if (hm->hash_map[index] == value) {
            return FALSE;
        } else if (hm->hash_map[index] == INT_MIN) {
            hm->hash_map[index] = value;
            hm->count++;
            return TRUE;
        }
        
        index = (index + 1) % BUCKET_SIZE;

    } while (index != start);

    return FALSE; 
}

int del(hash_map_t* hm, int value)
{
    if (hm->count == 0) {
        return FALSE;
    }

    int index = value % BUCKET_SIZE;
    if (index < 0) {
        index += BUCKET_SIZE;
    }

    int start = index;

    do {
        if (hm->hash_map[index] == value) {
            hm->hash_map[index] == INT_MIN;
            hm->count--;
            return TRUE;
        } else if (hm->hash_map[index] == INT_MIN) {
            return FALSE;
        }
        
        index = (index + 1) % BUCKET_SIZE;

    } while (index != start);

    return FALSE; 
}

void clear(hash_map_t* hm)
{
    hm->count == 0;
    size_t i;
    for (i = 0; i < BUCKET_SIZE; i++) {
        hm->hash_map[i] = INT_MIN;
    }
}

void print_hash_map(hash_map_t* hm)
{
    size_t i;
    for (i = 0; i < BUCKET_SIZE; i++) {
        if (hm->hash_map[i] == INT_MIN) {
            printf("empty ");
        }
        printf("%d ", hm->hash_map[i]);
    }    
}
