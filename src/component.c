#include <stdlib.h>
#include <string.h>
#include "component.h"
#include "hash.h"

Component_Type init_component_type(int length)
{
    Component_Type new_component;
    new_component.data = (void**)malloc(sizeof(void*) * length);
    new_component.hashmap = (int*)malloc(sizeof(int) * length);
    new_component.length = length;
    new_component.real_length = 0;
    for(int i = 0; i < length; i++)
    {
         new_component.hashmap[i] = -1;
    }
    return new_component;
}

void add_component(Component_Type *component_type, void *component_data, int entity_id)
{
    component_type->data[component_type->real_length] = component_data;
    component_type->hashmap[hash(entity_id, component_type->length)] = component_type->real_length;
    component_type->real_length++;
}

void remove_component(Component_Type *component_type, int entity_id)
{
    int hash_result = hash(entity_id, component_type->length);
    component_type->data[hash_result] = component_type->data[component_type->real_length];
    component_type->hashmap[hash_result] = -1;
    component_type->data[component_type->real_length] = NULL;
    component_type->real_length--;
}

void *get_component(Component_Type *component_type, int entity_id)
{
    int hash_result = hash(entity_id, component_type->length);
    if(component_type->hashmap[hash_result] == -1)
    {
        return NULL;
    }
    else
    {
        return component_type->data[component_type->hashmap[hash_result]];
    }
}