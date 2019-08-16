#include "engine.h"
#include "modules/camera.h"
#include "modules/sprite.h"
#include "modules/utils.h"
#include "modules/transform.h"
#include "modules/box_collider.h"
#include "modules/tilemap.h"

#define MAX_SPRITES 500
#define MAX_BOX_COLLIDERS 500

static Camera cam;
static Tilemap tilemap;

typedef struct
{
    int health;
    Sprite sprite;
    Box_Collider col;
    Transform transform;
} Base_Entity;
Base_Entity player;

static void player_move()
{
    Vec2_Int movement = vec2_int_zero();

    if(input_get_key(SDL_SCANCODE_A))
    {
        movement.x = -1;
    }
    else if(input_get_key(SDL_SCANCODE_D))
    {
        movement.x = 1;
    }
    if(input_get_key(SDL_SCANCODE_W))
    {
        movement.y = -1;
    }
    else if(input_get_key(SDL_SCANCODE_S))
    {
        movement.y = 1;
    }

    // currently causes seg fault cause tile map isnt intialized
    //movement = tilemap_collision(&movement, &player.col, &tilemap);
    player.transform.pos.x += movement.x;
    player.transform.pos.y += movement.y;
}

void game_start()
{
    cam = camera_init(vec2_int_zero(), renderer);
    sprite_init_module(MAX_SPRITES);
    box_collider_init_module(MAX_BOX_COLLIDERS);

    player.health = 10;
    player.transform = transform_set(0, 0, NULL);
    player.sprite = sprite_init("Town.png", transform_set(0, 0, &player.transform), &cam);
    sprite_add(&player.sprite);
    player.col = box_collider_init(16, 16, transform_set(0, 0, &player.transform));
    box_collider_add(&player.col);
}

void game_update()
{
    player_move();
}

void game_cleanup()
{
    sprite_cleanup_module();
    box_collider_cleanup_module();
}

void game_render()
{
    sprite_render(&cam);
}