#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

extern Uint8 input_previous_keyboard_state[512];
extern Uint8 input_current_keyboard_state[512];
extern const Uint8 *input_keyboard_state_pointer;

int input_get_key_down(SDL_Scancode scancode);
int input_get_key(SDL_Scancode scancode);
int input_get_key_up(SDL_Scancode scancode);

typedef struct
{
    SDL_Scancode scancode;
    char *input_name;
} Game_Input;
extern Game_Input *game_inputs;
extern int number_of_game_inputs;

SDL_Scancode scancode_from_gi(const char *input_name, Game_Input *inputs, int length); 
int get_input_down(const char *input_name);
int get_input(const char *input_name);
int get_input_up(const char *input_name);