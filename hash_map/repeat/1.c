#include <limits.h>
#include <stddef.h>
#include "../hash.h"

void init_hash_map(hash_map_t* hm)
{
    int i;
    hm->count = 0;
    for (i = 0; i < BUCKET_SIZE; ++i) {
        hm->hash_map[i] = INT_MIN;
    }
}

int has_value(const hash_map_t* hm, int value)
{
    int index = value % BUCKET_SIZE;
    int start;
    if (index < 0) {
        index += BUCKET_SIZE;
    }

    start = index;
    do {
        if (hm->hash_map[start] == value) {
            return 1;
        } else if (hm->hash_map[start] == INT_MIN) {
            return 0;
        }

        start = (start + 1) % BUCKET_SIZE;
    } while (index != start);
    return 0;
}

int add(hash_map_t* hm, int value)
{
    int index = value % BUCKET_SIZE;
    int start;

    if (hm->count >= BUCKET_SIZE) {
        return -1;
    }

    if (index < 0) {
        index += BUCKET_SIZE;
    }
    start = index;
    do {
        if (hm->hash_map[start] == value) {
            return 1;
        } else if (hm->hash_map[start] == INT_MIN) {
            hm->hash_map[start] = value;
            hm->count++;
            return 1;
        }
        start = (start + 1) % BUCKET_SIZE;
    } while (start != index);
    return -1;
}

int del(hash_map_t* hm, int value)
{
    int index = value % BUCKET_SIZE;
    int start;
    if (hm->count == 0) {
        return -1;
    }

    if (index < 0) {
        index += BUCKET_SIZE;
    }
    start = index;
    do {
        if (hm->hash_map[start] == value) {
            hm->hash_map[start] = INT_MIN;
            hm->count--;
            return 1;
        } else if (hm->hash_map[start] == INT_MIN) {
            return -1;
        }

        start = (start + 1) % BUCKET_SIZE;
    } while (start != index);
    return -1;
}
