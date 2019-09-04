#pragma once
#include <stdlib.h>

typedef struct Hashmap
{
    int map_length;
    void **map;
} Hashmap;

uint32_t hash(uint32_t key, Hashmap *hm);
void hash_add(void *hash_element, uint32_t key, Hashmap *hm);