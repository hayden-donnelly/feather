#include "engine.h"

// Returns true if key was pressed this frame
int input_get_key_down(SDL_Scancode scancode)
{
    if(input_current_keyboard_state[scancode] && !input_previous_keyboard_state[scancode])
    {
        return 1;
    }
    return 0;
}

// Returns true of key is pressed
int input_get_key(SDL_Scancode scancode)
{
    if(input_current_keyboard_state[scancode])
    {
        return 1;
    }
    return 0;
}

// Returns true if key was released this frame
int input_get_key_up(SDL_Scancode scancode)
{
    if(!input_current_keyboard_state[scancode] && input_previous_keyboard_state[scancode])
    {
        return 1;
    }
    return 0;
}