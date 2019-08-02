#include "engine.h"

Player main_player;

void game_start()
{
    main_player.transform = set_transform(0, 0, NULL);
    main_player.sprite = init_sprite("Town.png", set_transform(0, 0, &main_player.transform));
    subscribe_to_sprites(&main_player.sprite);
    main_player.box_collider = init_box_collider(16, 16, set_transform(0, 0, &main_player.transform));
    subscribe_to_box_colliders(&main_player.box_collider);
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