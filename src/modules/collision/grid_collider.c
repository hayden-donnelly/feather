#include <stdlib.h>
#include "grid_collider.h"

// Determine which grid cell a set of coordinates are in.
int pos_to_grid_cell_id(int x, int y, Grid_Collider *grid_collider)
{
    int grid_x = (int)floor(x / grid_collider.cell_width);
    int grid_y = (int)floor(y / grid_collider.cell_height);
    return grid_y * grid_collider.grid_width + grid_x;
}

// Difference between some x coordinate and the nearest rightward vertical grid line.
int calc_right_delta(int x, Grid_Collider *grid_collider)
{
    int right = (int)floor(x / grid_collider.grid_width + 1) * grid_collider->cell_width;
    return right - x;
}

// Difference between sme x coordinate and the nearest leftward vertical grid line.
int calc_left_delta(int x, Grid_Collider *grid_collider)
{
    int left = (int)floor(x / grid_collider.grid_width) * grid_collider.cell_width;
    return x - left;
}

// Number of horizontal collision checks required.
int calc_hor_check_quantity(int move_x, int delta, Grid_Collider * grid_collider)
{
    return (int)floor((move_x - delta) / grid_collider.cell_width);
}

Collision_Info grid_collision(Component_Type *grid_collider, Component_Type *position, 
                                Box_Collider *box_collider, int move_x, int move_y)
{
    Collision_Info collision_info;
    collision_info.modified_move_x = 0;
    collision_info.modified_move_y = 0;

    // These will be used to compare the movement vectors generated after horizontal
    // and vertical collision checks respectively.
    int potential_move_x_1 = 0;
    int potential_move_y_1 = 0;
    // Temp values for testing.
    int potential_move_x_2 = 100;
    int potential_move_y_2 = 100;

    int hor_check_quantity = 0;
    int ver_check_quantity = 0;

    // This algorithm is gonna be sexy :)

    // Rightward movement.
    if(move_x > 0)
    {
        int right_delta = calc_right_delta(position->x, grid_collider);
        // Horizontal move within cell. No possibility for collision.
        if(move_x <= right_delta)
        {
            collision_info.modified_move_x = move_x;
        }
        else
        {
            hor_check_quantity = calc_hor_check_quantity(move_x, right_delta, grid_collider);
            int farthest_move_x = 0;
            // Check for collision upon moving into first new cell and then iterate for all other cells.
            // +1 is to push x coordinate into the next cell. I need to check if this is actually necessary.
            farthest_move_x += right_delta + 1;
            for(int i = 0; i < hor_check_quantity; i++)
            {
                int current_y_movement = (int)(move_y * (farthest_move_x / move_x));
                int current_y = position->y + current_y_movement;
                int grid_cell_id = pos_to_grid_cell_id(position->x + farthest_move_x, current_y, grid_collider);

                if(grid_collider.collision_ids[grid_cell_id] == 1)
                {
                    // A collision has been detected.
                    potential_move_x_1 = farthest_move_x - 1;
                    potential_move_y_1 = current_y_movement;
                    break;
                }
                else
                {
                    farthest_move_x += grid_collider.cell_width;
                }
            }
        }
    }

    // Will develop this once the general logic has been laid out for rightward movement.
    else if(move_x < 0)
    {
        // Horizontal move within cell. No possibility for collision.
        if(move_y <= calc_left_delta(position->x, grid_collider))
        {
            collision_info.modified_move_x = move_x;
        }
        else
        {
            hor_check_quantity = calc_hor_check_quantity(move_x, right_delta, grid_collider);
        }
    }

    // Only use the smallest potential move because it is the one which stops at the first collisions.
    if(sqrt((double)(pow(potential_move_x_1, 2) + pow(potential_move_y_1, 2)))
       < sqrt((double)(pow(potential_move_x_2, 2) + pow(potential_move_y_2, 2))))
    {
        collision_info.modified_move_x = potential_move_x_1;
        collision_info.modified_move_y = potential_move_y_1;
    }
    else
    {
        collision_info.modified_move_x = potential_move_x_2;
        collision_info.modified_move_y = potential_move_y_2;
    }

    return collision_info;
}