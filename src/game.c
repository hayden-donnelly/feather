#include <stdio.h>
#include "engine.h"
#include "component.h"
#include <SDL2/SDL_image.h>

#define MAX_ENTITIES 500

void game_init(void)
{
    components = malloc(sizeof(Components));
    components->health = init_component_type(MAX_ENTITIES);
    components->position = init_component_type(MAX_ENTITIES);
    components->anim_controller = init_component_type(MAX_ENTITIES);
    components->tilemap = init_component_type(1);

    // Random components
    Health *health = malloc(sizeof(Health));
    health->enitity_id = 30;
    health->hp = 20;
    Health *health4 = malloc(sizeof(Health));
    health4->enitity_id = 31;
    health4->hp = 5;

    add_component(&components->health, health, health->enitity_id);
    add_component(&components->health, health4, health4->enitity_id);

    Health *health2 = get_component(&components->health, 30);
    health2->hp -= 10;
    printf("HP: %d\n", health2->hp);

    Health *health3 = get_component(&components->health, 30);
    printf("HP: %d\n", health3->hp);

    remove_component(&components->health, 30);
    if(get_component(&components->health, 30) == NULL)
    {
        printf("it works\n");
    }

    Health *health5 = get_component(&components->health, 31);
    printf("HP2: %d\n", health5->hp);
    health3 = get_component(&components->health, 30);
    if(health3 != NULL) { printf("HP: %d\n", health3->hp); }

    Position *pos1 = malloc(sizeof(Position));
    pos1->entity_id = 30;
    pos1->x = 50;
    pos1->y = 50;
    add_component(&components->position, pos1, 30);

    // Animation
    Anim_Controller *anim_controller1 = malloc(sizeof(Anim_Controller));
    anim_controller1->entity_id = 30;
    anim_controller1->sprite = malloc(sizeof(Sprite));
    anim_controller1->sprite->tile_width = 16;
    anim_controller1->sprite->tile_height = 16;
    anim_controller1->sprite->number_of_tiles_horizontal = 3;
    anim_controller1->sprite->number_of_tiles_vertical = 3;
    anim_controller1->sprite->tex = IMG_LoadTexture(renderer, "assets/16x16_test.png");
    SDL_Rect draw_rect;
    draw_rect.x = 0;
    draw_rect.y = 0;
    draw_rect.w = 16;
    draw_rect.h = 16;
    anim_controller1->sprite->src = draw_rect;
    anim_controller1->sprite->dst = draw_rect;
    anim_controller1->anims = malloc(sizeof(Anim)*3);
    anim_controller1->anim_id = 0;
    anim_controller1->frame_id = 0;
    anim_controller1->default_anim_id = 0;

    Anim anim1;  
    anim1.frame_count = 6;
    anim1.tile_ids = malloc(sizeof(int)*6);
    anim1.tile_ids[0] = 1;
    anim1.tile_ids[1] = 2;
    anim1.tile_ids[2] = 3;
    anim1.tile_ids[3] = 4;
    anim1.tile_ids[4] = 5;
    anim1.tile_ids[5] = 6;
    anim1.loop = 1;
    anim1.speed = 0.3f;
    anim_controller1->anims[0] = anim1;

    add_component(&components->anim_controller, anim_controller1, 30);

    // Tilemap
    Tilemap *tilemap1 = malloc(sizeof(Tilemap));
    tilemap1->sprite_ids = malloc(sizeof(int)*400);
    for(int i = 0; i < 400; i++)
    {
        tilemap1->sprite_ids[i] = 2;
    }
    tilemap1->map_width = 20;
    tilemap1->map_height = 20;
    tilemap1->entity_id = 500;
    tilemap1->sprite = malloc(sizeof(Sprite));
    tilemap1->sprite->number_of_tiles_horizontal = 4;
    tilemap1->sprite->number_of_tiles_vertical = 4;
    tilemap1->sprite->tile_width = 16;
    tilemap1->sprite->tile_height = 16;
    tilemap1->sprite->tex = IMG_LoadTexture(renderer, "assets/16x16_bricks.png");
    tilemap1->sprite->dst = draw_rect;
    tilemap1->sprite->src = draw_rect;

    add_component(&components->tilemap, tilemap1, 500);

    // Input 
    number_of_game_inputs = 4;
    game_inputs = malloc(sizeof(Game_Input)*4);

    Game_Input left;
    left.scancode = SDL_SCANCODE_D;
    left.input_name = "left";
    game_inputs[0] = left;

    Game_Input right;
    right.scancode = SDL_SCANCODE_A;
    right.input_name = "right";
    game_inputs[1] = right;

    Game_Input up;
    up.scancode = SDL_SCANCODE_W;
    up.input_name = "up";
    game_inputs[2] = up;

    Game_Input down;
    down.scancode = SDL_SCANCODE_S;
    down.input_name = "down";
    game_inputs[3] = down;
}

void game_update(void)
{
    update_anim(&components->anim_controller);
    
    Position *player_pos = get_component(&components->position, 30);

    if(player_pos)
    {
        if(get_input("left"))
        {
            player_pos->x += 1;
        }
        else if(get_input("right"))
        {
            player_pos->x -= 1;
        }
        else if(get_input("up"))
        {
            player_pos->y -= 1;
        }
        else if(get_input("down"))
        {
            player_pos->y += 1;
        }
    }
}

void game_cleanup(void)
{
    printf("Game Cleanup\n");
}

void game_render(void)
{
    render_tilemap(&components->tilemap, &components->position);
    render_anim(&components->anim_controller, &components->position);
}