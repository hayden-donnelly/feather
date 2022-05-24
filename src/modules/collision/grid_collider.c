#include <stdlib.h>
#include <stdio.h>
#include "grid_collider.h"

// Determine which grid cell a set of coordinates are in.
int pos_to_grid_cell_id(int x, int y, Grid_Collider *grid_collider)
{
    x = abs(x);
    y = abs(y);
    int grid_x = (int)floor((double)x / (double)grid_collider->cell_width);
    //printf("X: %d\n", x);
    //printf("Grid X: %d\n", grid_x);
    int grid_y = (int)floor((double)y / (double)grid_collider->cell_height);
    //printf("Grid Y: %d\n", grid_y);
    return grid_y * grid_collider->grid_width + grid_x;
}

// Difference between some x coordinate and the nearest rightward vertical grid line.
int calc_right_delta(int x, Grid_Collider *grid_collider)
{
    // The fact that I have to take abs here may mean there is something wrong with the coorindate system.
    x = abs(x);
    int right = (int)floor((double)x / (double)grid_collider->cell_width + 1) * grid_collider->cell_width;
    //printf("Right: %d\n", right);
    //printf("Floored: %d\n", (int)floor(x/grid_collider->grid_width+1));
    //printf("GW: %d\n", grid_collider->grid_width);
    //printf("Calc 1: %d\n", (int)((double)x/(double)grid_collider->grid_width)); // This.
    //printf("X: %d\n", x);
    return right - x;
}

// Difference between sme x coordinate and the nearest leftward vertical grid line.
int calc_left_delta(int x, Grid_Collider *grid_collider)
{
    int left = (int)floor((double)x / (double)grid_collider->grid_width) * grid_collider->cell_width;
    return x - left;
}

// Number of horizontal collision checks required.
int calc_hor_check_quantity(int move_x, int delta, Grid_Collider * grid_collider)
{
    return (int)floor((double)(move_x - delta) / (double)grid_collider->cell_width) + 1;
}

Collision_Info grid_collision(Component_Type *grid_collider_type, Component_Type *position_type, 
                                Box_Collider *box_collider, int move_x, int move_y)
{
    // It's kind of weird how component types are passed into this function.
    // Why not just grab them straight from the components struct?

    Grid_Collider *grid_collider = grid_collider_type->data[0];
    // Player position. Change later to remove hardcode.
    Position *position = get_component(position_type, 32);

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

    //printf("1\n");
    //printf("asdasd: %d\n", calc_right_delta(position->x, grid_collider));
    // Rightward movement.
    if(move_x > 0)
    {
        //printf("2\n");
        int right_delta = calc_right_delta(position->x+16, grid_collider);
        // Horizontal move within cell. No possibility for collision.
        //printf("3\n");
        //printf("Right Delta: %d\n", right_delta);
        if(abs(move_x) < abs(right_delta))
        {
            //printf("4\n");
            potential_move_x_1 = move_x;
        }
        else
        {
            //printf("5\n");
            hor_check_quantity = calc_hor_check_quantity(move_x, right_delta, grid_collider);
            //printf("Hor: %d\n", hor_check_quantity);
            //printf("6\n");
            int farthest_move_x = 0;
            // Check for collision upon moving into first new cell and then iterate for all other cells.
            // +1 is to push x coordinate into the next cell. I need to check if this is actually necessary.
            farthest_move_x += right_delta + 1;
            for(int i = 0; i < hor_check_quantity; i++)
            {
                //printf("7\n");
                int current_y_movement = (int)(move_y * (farthest_move_x / move_x));
                int current_y = position->y + current_y_movement;
                int grid_cell_id = pos_to_grid_cell_id(position->x + farthest_move_x, current_y, grid_collider);
                //printf("Position X: %d\n", position->x);
                printf("Right Delta: %d\n", right_delta);
                //printf("8\n");
                //printf("Cell ID: %d\n", grid_cell_id);

                if(grid_collider->collision_ids[grid_cell_id] == 1)
                {
                    printf("9\n");
                    // A collision has been detected.
                    potential_move_x_1 = farthest_move_x - 1;
                    potential_move_y_1 = current_y_movement;
                    break;
                }
                else
                {
                    //printf("10\n");
                    farthest_move_x += grid_collider->cell_width;
                    //potential_move_x_1 = farthest_move_x;
                    if(farthest_move_x > move_x)
                    {
                        printf("Yes\n");
                        potential_move_x_1 = move_x;
                        break;
                    }
                }
            }
        }
    }

    // Will develop this once the general logic has been laid out for rightward movement.
    /*else if(move_x < 0)
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
    }*/

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