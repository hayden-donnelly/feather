#pragma once

typedef struct
{
    void **data;
    int *hashmap;
    int length; // TODO: Change name to max_length
    int real_length;
} Component_Type;

typedef struct
{
    Component_Type health;
    Component_Type position;
    Component_Type anim_controller;
    Component_Type tilemap;
    Component_Type grid_collider;
    Component_Type box_collider;
} Components;

extern Components *components;

Component_Type init_component_type(int length);
void add_component(Component_Type *component_type, void *component_data, int entity_id);
void remove_component(Component_Type *component_type, int entity_id);
void *get_component(Component_Type *component_type, int entity_id);

#include "modules/health.h"
#include "modules/position.h"
#include "modules/rendering/animation.h"
#include "modules/rendering/tilemap.h"
#include "modules/collision/box_collider.h"
