#include <stdlib.h>
#include "grid_collider.h"

// Determine which grid cell a set of coordinates are in.
int pos_to_grid_cell_id(int x, int y, Grid_Collider *grid_collider)
{
    int grid_x = (int)floor(x / grid_collider.cell_width);
    int grid_y = (int)floor(y / grid_collider.cell_height);
    return grid_y * grid_collider.grid_width + grid_x;
}

// Deprecated, will delete soon.
int calculate_deltas(int x, int y, Grid_Collider *grid_collider)
{
    int above = (int)floor(y / grid_collider.grid_height) * grid_collider.cell_height;
    int above_delta = y - above;

    int below = (int)floor(y / grid_collider.grid_height + 1) * grid_collider.cell_height;
    int below_delta = below - y;

    int right = (int)floor(x / grid_collider.grid_width + 1) * grid_collider.cell_width;
    int right_delta = right - x;

    int left = (int)floor(x / grid_collider.grid_width) * grid_collider.cell_width;
    int left_delta = x - left;
}

// Difference between some x coordinate and the nearest rightward vertical grid line.
int calc_right_delta(int x, Grid_Collider *grid_collider)
{
    int right = (int)floor(x / grid_collider.grid_width + 1) * grid_collider.cell_width;
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

    int hor_check_quantity = 0;
    int ver_check_quantity = 0;

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
            for(int i = 0; i < hor_check_quantity; i++)
            {
                // These variable names suck so I will rename them soon.
                farthest_move_x += grid_collider.cell_width;
                collision_info.modified_move_x = farthest_move_x;
                
                int current_y = position->y + (int)(move_y * (farthest_move_x / move_x));
                int grid_cell_id = pos_to_grid_cell_id(position->x + farthest_move_x, current_y, grid_collider);
                
                if(grid_collider.collision_ids[grid_cell_id] == 1)
                {
                    // A collision has been detected.
                    break;
                }
            }
        }
    }

    // Will develop this one the general logic has been laid out for rightward movement.
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

    return collision_info;
}