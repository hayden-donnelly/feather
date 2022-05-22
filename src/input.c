#include "input.h"

// Returns true if key was pressed this frame
int input_get_key_down(SDL_Scancode scancode)
{
    if(input_current_keyboard_state[scancode] && !input_previous_keyboard_state[scancode])
    {
        return 1;
    }
    return 0;
}

// Returns true if key is pressed
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

// The following functions provide a layer of abstraction that allows for
// keybinding and alternative input methods (controllers).
SDL_Scancode scancode_from_gi(const char *input_name, Game_Input *inputs, int length)
{
    for(int i = 0; i < length; i++)
    {
        if(inputs[i].input_name == input_name)
        {
            return inputs[i].scancode;
        }
    }
    // Can't return NULL, so return period since it is unlikely
    // to be used for gameplay.
    return SDL_SCANCODE_PERIOD;
    //return NULL;
}   

int get_input_down(const char *input_name)
{
    SDL_Scancode sc = scancode_from_gi(input_name, game_inputs, number_of_game_inputs);
    return input_get_key_down(sc);
}

int get_input(const char *input_name)
{
    SDL_Scancode sc = scancode_from_gi(input_name, game_inputs, number_of_game_inputs);
    return input_get_key(sc);
}

int get_input_up(const char *input_name)
{
    SDL_Scancode sc = scancode_from_gi(input_name, game_inputs, number_of_game_inputs);
    return input_get_key_up(sc);
}