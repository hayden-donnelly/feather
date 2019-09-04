#include "hashmap.h"

uint32_t hash(uint32_t key, Hashmap *hm)
{
    long l = 2654435769;
    return (key * l >> 32) % hm->map_length;    // black magic
}

void hash_add(void *hash_element, uint32_t key, Hashmap *hm)
{
    key = hash(key, hm);
    hm->map[key] = hash_element;
}   

// TODO: hash_remove