#include "engine.h"
#include "modules/camera.h"
#include "modules/sprite.h"
#include "modules/utils.h"
#include "modules/transform.h"
#include "modules/box_collider.h"
#include "modules/tilemap.h"

//Player main_player;

Sprite test;
Camera cam;

enum component_tag
{
    sprite_tag = 1,
    col_tag = 2,
    tilemap_tag = 3
};

typedef union
{
    Sprite sprite;
    Box_Collider col;
    Tilemap tilemap;
} Component;

typedef struct
{
    int component_tag;
    Component component;

} Tagged_Component;

typedef struct 
{
    Transform transform;
    Tagged_Component *components;
} Entity;

#define MAX_ENTITIES 500
Entity *entities[MAX_ENTITIES];

Entity player;

void game_start()
{
    cam = camera_init(vec2_int_zero(), renderer);
    test = sprite_init("Town.png", transform_set(0, 0, NULL), &cam);
    sprite_subscribe(&test);

    /*main_player.transform = set_transform(0, 0, NULL);
    main_player.sprite = init_sprite("Town.png", set_transform(0, 0, &main_player.transform));
    subscribe_to_sprites(&main_player.sprite);
    main_player.box_collider = init_box_collider(16, 16, set_transform(0, 0, &main_player.transform));
    subscribe_to_box_colliders(&main_player.box_collider);*/

    player.transform = transform_set(0, 0, NULL);
    player.components = malloc(sizeof(Component));
    player.components[0].component = (Component)sprite_init("Town.png", transform_set(0, 0, &player.transform), &cam);
    player.components[0].component_tag = sprite_tag;
    entities[0] = &player;

    for(int i = 0; i < MAX_ENTITIES; i++)
    {
        if(entities[i] != NULL && entities[i]->components[0].component_tag == sprite_tag)
        {
            printf("It's a sprite\n");
        }
    }
}

void game_update()
{
    if(input_get_key_down(SDL_SCANCODE_A))
    {
        printf("Hello World\n");
        printf("Hello World\n");
    }
}

void game_cleanup()
{

}

void game_render()
{
    sprite_render(&cam);
}