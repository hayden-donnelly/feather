#include <stdlib.h>
#include <stdio.h>
#include "grid_collider.h"

// Determine which grid cell a set of coordinates are in.
int pos_to_grid_cell_id(int x, int y, int cell_offset, Grid_Collider *grid_collider)
{
    x = abs(x);
    y = abs(y);
    int grid_x = (int)floor((double)x / (double)grid_collider->cell_width);
    int grid_y = (int)floor((double)y / (double)grid_collider->cell_height);
    return grid_y * grid_collider->grid_width + grid_x + cell_offset;
}

// Calculates the difference between some coordinate and specified grid line.
// Set coordinate = x and cell_size = cell_width to calculate distance to vertical grid line.
// Set coordinate = y and cell_size = cell_height to calculate distance to horizontal grid line.
// When cell_offset = 0, function will calculate the distance to the line that is to the left
// or above coordinate. Inversely, function will calculatte distance to the line that is to the right
// or below cordinate when cell_offset = 1.
int calc_delta(int coordinate, int cell_size, int cell_offset)
{
    coordinate = abs(coordinate);
    int cell_line_coordinate = (int)floor((double)coordinate / (double)cell_size) * cell_size;
    cell_line_coordinate += cell_size * cell_offset;
    return abs(coordinate - cell_line_coordinate);
}

// Number of collision checks required.
int calc_check_quantity(int move, int delta, int cell_size)
{
    return (int)floor((double)(abs(move) - abs(delta)) / (double)cell_size) + 1;
}

// See comment above calc_delta() for explanation of cell_offset. It is passed into that function.
int hor_collision(int move_x, int move_y, int pos_x, int pos_y, int cell_offset, Grid_Collider *grid_collider)
{
    int move_sign_x = (int)copysign(1, move_x);
    int delta = calc_delta(pos_x, grid_collider->cell_width, cell_offset);
    printf("delta %d\n", delta);

    if(abs(move_x) < delta)
    {
        return move_x;
    }
    else
    {
        int hor_check_quantity = calc_check_quantity(move_x, delta, grid_collider->cell_width);
        int modified_move_x = delta * move_sign_x;
        for(int i = 0; i < hor_check_quantity; i++)
        {
            int current_move_y = (int)(move_y * abs(modified_move_x / move_x));
            int current_pos_y = pos_y + current_move_y;
            int grid_cell_id = pos_to_grid_cell_id(pos_x + modified_move_x, current_pos_y, cell_offset, grid_collider);
        
            if(grid_collider->collision_ids[grid_cell_id] == 1)
            {
                // A collision has been detected.
                printf("Collision has been detected.\n");
                return modified_move_x + cell_offset;
            }
            else
            {
                modified_move_x += grid_collider->cell_width * move_sign_x;
                if(abs(modified_move_x) > abs(move_x))
                {
                    // A full movement has been completed with no collision.
                    return move_x;
                }
            }
        }
    }
    return 0;
}



int ver_collision(int move_x, int move_y, int pos_x, int pos_y, int cell_offset, Grid_Collider *grid_collider)
{
    int move_sign_y = (int)copysign(1, move_y);
    int delta = calc_delta(pos_y, grid_collider->cell_height, cell_offset);
    printf("delta %d\n", delta);

    if(abs(move_y) < delta)
    {
        return move_y;
    }
    else
    {
        int ver_check_quantity = calc_check_quantity(move_y, delta, grid_collider->cell_height);
        int modified_move_y = delta * move_sign_y;
        for(int i = 0; i < ver_check_quantity; i++)
        {
            int current_move_x = (int)(move_x * abs(modified_move_y / move_y));
            int current_pos_x = pos_x + current_move_x;
            int grid_cell_id = pos_to_grid_cell_id(current_pos_x, pos_y + modified_move_y, cell_offset, grid_collider);
        
            if(grid_collider->collision_ids[grid_cell_id] == 1)
            {
                // A collision has been detected.
                printf("Collision has been detected.\n");
                return modified_move_y + cell_offset;
            }
            else
            {
                modified_move_y += grid_collider->cell_height * move_sign_y;
                if(abs(modified_move_y) > abs(move_y))
                {
                    // A full movement has been completed with no collision.
                    return move_y;
                }
            }
        }
    }
    return 0;
}


Collision_Info grid_collision_old(Component_Type *grid_collider_type, Component_Type *position_type, 
                                Box_Collider *box_collider, int move_x, int move_y)
{
    // It's kind of weird how component types are passed into this function.
    // Why not just grab them straight from the components struct?

    // TODO: iterate through all grid colliders
    Grid_Collider *grid_collider = grid_collider_type->data[0];
    // Player position. Change later to remove hardcode.
    Position *position = get_component(position_type, 32);
    Position *position2 = get_component(position_type, 30);

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

    // Horizontal
    int top_movement = 0;
    int bottom_movement = 0;
    // Vertical
    int left_movement = 0;
    int right_movement = 0;

    // Rightward movement.
    if(move_x < 0)
    {
        top_movement = hor_collision(
            move_x, move_y, position->x-position2->x-16, 
            position->y-position2->y, 1, grid_collider
        );

        bottom_movement = hor_collision(move_x, move_y, position->x-position2->x-16, 
                                            position->y-position2->y-16, 1, grid_collider);
    }
    // Leftward movement.
    else if(move_x > 0)
    {
        top_movement = hor_collision(move_x, move_y, position->x-position2->x, 
                                        position->y-position2->y, 0, grid_collider);

        bottom_movement = hor_collision(move_x, move_y, position->x-position2->x, 
                                            position->y-position2->y-16, 0, grid_collider);
    }
    // Downward movement.
    if(move_y < 0)
    {
        left_movement = ver_collision(move_x, move_y, position->x-position2->x, 
                                        position->y-position2->y-16, 1, grid_collider);

        right_movement = ver_collision(move_x, move_y, position->x-position2->x-16, 
                                        position->y-position2->y-16, 1, grid_collider);
    }
    // Upward movement.
    else if(move_y > 0)
    {
        left_movement = ver_collision(move_x, move_y, position->x-position2->x, 
                                        position->y-position2->y, 0, grid_collider);   

        right_movement = ver_collision(move_x, move_y, position->x-position2->x-16, 
                                        position->y-position2->y, 0, grid_collider);
    }

    // Only use the smallest potential move because it is the one which stops at the first collisions.
    /*if(sqrt((double)(pow(potential_move_x_1, 2) + pow(potential_move_y_1, 2)))
       < sqrt((double)(pow(potential_move_x_2, 2) + pow(potential_move_y_2, 2))))
    {
        collision_info.modified_move_x = potential_move_x_1;
        collision_info.modified_move_y = potential_move_y_1;
    }
    else
    {
        collision_info.modified_move_x = potential_move_x_2;
        collision_info.modified_move_y = potential_move_y_2;
    }*/

    collision_info.modified_move_x = 
        (abs(top_movement) > abs(bottom_movement)) ? bottom_movement : top_movement;
    collision_info.modified_move_y = 
        (abs(left_movement) > abs(right_movement)) ? right_movement : left_movement;

    return collision_info;
}

Collision_Info grid_collision(
    Component_Type *grid_collider_type, Component_Type *position_type, 
    int move_x, int move_y)
{
    Grid_Collider *grid_collider = grid_collider_type->data[0];
    Collision_Info collision_info;
    collision_info.modified_move_x = 0;
    collision_info.modified_move_y = 0;

    Position *player_position = get_component(position_type, 30);
    int starting_x = player_position->x + move_x;
    int starting_y = player_position->y + move_y;

    int grid_x = (int)floor((double)starting_x / (double)grid_collider->cell_width) + 1;
    int grid_y = (int)floor((double)starting_y / (double)grid_collider->cell_height);
    int grid_id = grid_y * grid_collider->grid_width + grid_x;
    
    if(move_x != 0 || move_y != 0)
    {
        printf("grid_x: %d, grid_y: %d\n", grid_x, grid_y);
    }

    if(grid_collider->collision_ids[grid_id] == 0)
    {
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = move_y;
    }

    return collision_info;
}