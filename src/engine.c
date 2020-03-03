#include <stdio.h>
#include "engine.h"
#include "game.h"

static double timer_last;
static double timer_now;
static double timer_dt;
static double timer_fixed_dt;
static double timer_accumulator;

double read_timer_dt(void) { return timer_dt; }

static void events(SDL_Event event)
{
    // Handle all events, making sure previous and current input states are updated properly
    memcpy(input_previous_keyboard_state, input_current_keyboard_state, 512);
    while(SDL_PollEvent(&event)) 
    {
        if(event.type == SDL_QUIT) 
        {
            printf("Quit\n");
            running = 0;
            break;
        }
    }
    memcpy(input_current_keyboard_state, input_keyboard_state_pointer, 512);
}

static void render(void)
{
    SDL_RenderClear(renderer);
    game_render();
    SDL_RenderPresent(renderer); 
}

void loop(void)
{
    SDL_Event event;
    running = 1;
    while(running)
    {
        printf("%s", SDL_GetError());
        timer_last = timer_now;
        timer_now = SDL_GetPerformanceCounter();
        timer_dt = ((timer_now - timer_last)/(double)SDL_GetPerformanceFrequency());
        timer_accumulator += timer_dt;

        while (timer_accumulator >= timer_fixed_dt)
        {
            events(event);
            game_update();
            timer_accumulator -= timer_fixed_dt;
        }

        render();
    }
}

int engine_init(void)
{
    int window_width = 1280;
    int window_height = 720;
    int target_render_width = 160;
    int target_render_height = 160;

    // Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) 
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                window_width, window_height, SDL_WINDOW_MAXIMIZED);
    if(window == NULL)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL)
    {
        printf("Failed to create renderer %s\n", SDL_GetError());
        return 1;
    }
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize(renderer, target_render_width, target_render_height);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    input_keyboard_state_pointer = SDL_GetKeyboardState(NULL);

    // Init timer
    timer_now = SDL_GetPerformanceCounter();
    timer_last = 0;
    timer_dt = 0;
    timer_fixed_dt = 1.0/59.9;
    timer_accumulator = 0;

    return 0;
}

void engine_cleanup(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();  
}