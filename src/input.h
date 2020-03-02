#pragma once
#include <SDL2/SDL.h>

Uint8 input_previous_keyboard_state[512];
Uint8 input_current_keyboard_state[512];
const Uint8 *input_keyboard_state_pointer;

int input_get_key_down(SDL_Scancode scancode);
int input_get_key(SDL_Scancode scancode);
int input_get_key_up(SDL_Scancode scancode);