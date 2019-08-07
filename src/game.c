#include "engine.h"
#include "modules/camera.h"
#include "modules/sprite.h"
#include "modules/utils.h"
#include "modules/transform.h"
#include "modules/box_collider.h"
#include "modules/tilemap.h"

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

Entity player;

typedef struct
{
    int health;
} main_player;

void game_start()
{
    cam = camera_init(vec2_int_zero(), renderer);
    test = sprite_init("Town.png", transform_set(0, 0, NULL), &cam);
    sprite_add(&test);

    player.transform = transform_set(0, 0, NULL);
    player.components = malloc(sizeof(Component));
    player.components[0].component = (Component)sprite_init("Town.png", transform_set(0, 0, &player.transform), &cam);
    player.components[0].component_tag = sprite_tag;
}

void game_update()
{
    if(input_get_key_down(SDL_SCANCODE_A))
    {
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