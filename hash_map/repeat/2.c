#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include "../hash.h"

void init_hash_map(hash_map_t* hm)
{
	size_t i;
	for (i = 0; i < BUCKET_SIZE; i++) {
		hm->hash_map[i] = INT_MIN;
	}		
	hm->count = 0;
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
		if (hm->hash_map[index] == INT_MIN) {
			return FALSE;
		} else if (hm->hash_map[index] == value) {
			return TRUE;
		}
		index = (index + 1) % BUCKET_SIZE;
	} while (start != index);
	return FALSE;
}

int add(hash_map_t* hm, int value)
{
	int index = value % BUCKET_SIZE;
	int start;
	
	if (hm->count >= BUCKET_SIZE) {
		return FALSE;
	}

	if (index < 0) {
		index += BUCKET_SIZE;
	}
	start = index;
	do {
		if (hm->hash_map[index] == INT_MIN) {
			hm->hash_map[index] = value;
			hm->count++;
			return TRUE;
		} else if (hm->hash_map[index] == value) {
			return FALSE;
		}
		index = (index + 1) % BUCKET_SIZE;
	} while (start != index);
	return FALSE;
}

int del(hash_map_t* hm, int value)
{
	int index = value % BUCKET_SIZE;
	int start;
	
	if (hm->count <= 0) {
		return FALSE;
	}
	
	if (index < 0) {
		index += BUCKET_SIZE;
	}

	start = index;
	do {
		if (hm->hash_map[index] == INT_MIN) {
			return FALSE;
		} else if (hm->hash_map[index] == value) {
			hm->hash_map[index] = INT_MIN;
			hm->count--;
			return TRUE;
		}
		index = (index + 1) % BUCKET_SIZE;
	} while (start != index);
	return FALSE;
}

void clear(hash_map_t* hm)
{
	size_t i;
	for (i = 0; i < BUCKET_SIZE; i++) {
		hm->hash_map[i] = INT_MIN;
	}
	hm->count = 0;
}

void print_hash_map(hash_map_t* hm)
{
	size_t i;
	int value;
	for (i = 0; i < BUCKET_SIZE; i++) {
		value = hm->hash_map[i];
		if (value != INT_MIN) {
			printf("%d ", value);
		} else {
			printf("NONE ");
		}
	}
	printf("\n");
}
