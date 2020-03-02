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
    anim_controller1->anims[0] = anim1;

    add_component(&components->anim_controller, anim_controller1, 30);
}

void game_update(void)
{
    update_anim(&components->anim_controller);
}

void game_cleanup(void)
{
    printf("Game Cleanup\n");
}

void game_render(void)
{
    render_anim(&components->anim_controller);
}