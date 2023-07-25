#include <stdlib.h>
#include <stdio.h>
#include "grid_collider.h"

int get_grid_x(int x, Grid_Collider *grid_collider)
{
    return (int)floor((double)x / (double)grid_collider->cell_width);
}

int get_grid_y(int y, Grid_Collider *grid_collider)
{
    return (int)floor((double)y / (double)grid_collider->cell_height);
}

int position_to_grid_id(int x, int y, Grid_Collider *grid_collider)
{
    int grid_x = get_grid_x(x, grid_collider);
    int grid_y = get_grid_y(y, grid_collider);
    int grid_id = grid_y * grid_collider->grid_width + grid_x;
    printf("x: %d\n", grid_x);
    return grid_id;
}

int sign(int number)
{
    if(number > 0) { return 1; }
    if(number < 0) { return -1; }
    return 0;
}

Collision_Info simple_grid_collision(
    Component_Type *grid_collider_type, Component_Type *position_type, 
    int move_x, int move_y, int position_id, int grid_collider_id
)
{
    Position *player_position = get_component(position_type, position_id);
    int new_x = player_position->x + move_x;
    int new_y = player_position->y + move_y;

    Collision_Info collision_info;
    collision_info.modified_move_x = move_x;
    collision_info.modified_move_y = move_y;

    Grid_Collider *grid_collider = get_component(grid_collider_type, grid_collider_id);
    int grid_id = position_to_grid_id(new_x, new_y, grid_collider);

    if(grid_collider->collision_ids[grid_id] == 1)
    {
        collision_info.modified_move_x = 0;
        collision_info.modified_move_y = 0;
    }
    
    if(move_x != 0 || move_y != 0)
    {
        //printf("grid_x: %d, grid_y: %d\n", grid_x, grid_y);
        printf("Collision ID: %d\n", grid_collider->collision_ids[grid_id]);
    }

    return collision_info;
}

Collision_Info complex_grid_collision(
    Component_Type *grid_collider_type, Component_Type *position_type, 
    Component_Type *box_collider_type, int move_x, int move_y, int mover_id, 
    int grid_collider_id
)
{
    Position *mover_position = get_component(position_type, mover_id);
    Box_Collider *mover_collider = get_component(box_collider_type, mover_id);
    Grid_Collider *grid_collider = get_component(grid_collider_type, grid_collider_id);

    Collision_Info collision_info;
    collision_info.modified_move_x = 0;
    collision_info.modified_move_y = 0;

    if(move_x > 0)
    {
        int top_right_x = mover_position->x + mover_collider->w + move_x;
        int top_right_y = mover_position->y;
        int bot_right_x = top_right_x;
        int bot_right_y = mover_position->y + mover_collider->h;

        int top_right_id = position_to_grid_id(top_right_x, top_right_y, grid_collider);
        int bot_right_id = position_to_grid_id(bot_right_x, bot_right_y, grid_collider);
        if(grid_collider->collision_ids[top_right_id] == 0 && 
           grid_collider->collision_ids[bot_right_id] == 0)
        {
            collision_info.modified_move_x = move_x;
        }
    }
    else if(move_x < 0)
    {
        int top_left_x = mover_position->x + move_x;
        int top_left_y = mover_position->y;
        int bot_left_x = top_left_x;
        int bot_left_y = mover_position->y + mover_collider->h;

        int top_left_id = position_to_grid_id(top_left_x, top_left_y, grid_collider);
        int bot_left_id = position_to_grid_id(bot_left_x, bot_left_y, grid_collider);
        if(grid_collider->collision_ids[top_left_id] == 0 && 
           grid_collider->collision_ids[bot_left_id] == 0)
        {
            collision_info.modified_move_x = move_x;
        }
    }

    if(move_y < 0)
    {
        int top_left_x = mover_position->x;
        int top_left_y = mover_position->y + move_y;
        int top_right_x = mover_position->x + mover_collider->w;
        int top_right_y = top_left_y;

        int top_left_id = position_to_grid_id(top_left_x, top_left_y, grid_collider);
        int top_right_id = position_to_grid_id(top_right_x, top_right_y, grid_collider);
        if(grid_collider->collision_ids[top_left_id] == 0 && 
           grid_collider->collision_ids[top_right_id] == 0)
        {
            collision_info.modified_move_y = move_y;
        }
    }
    else if(move_y > 0)
    {
        int bot_left_x = mover_position->x;
        int bot_left_y = mover_position->y + mover_collider->h + move_y;
        int bot_right_x = mover_position->x + mover_collider->w;
        int bot_right_y = bot_left_y;

        int bot_left_id = position_to_grid_id(bot_left_x, bot_left_y, grid_collider);
        int bot_right_id = position_to_grid_id(bot_right_x, bot_right_y, grid_collider);
        if(grid_collider->collision_ids[bot_left_id] == 0 && 
           grid_collider->collision_ids[bot_right_id] == 0)
        {
            collision_info.modified_move_y = move_y;
        }
    }

    return collision_info;
}

Collision_Info perfect_grid_collision(
    Component_Type *grid_collider_type, Component_Type *position_type, 
    Component_Type *box_collider_type, int move_x, int move_y, int mover_id, 
    int grid_collider_id
)
{
    Position *mover_position = get_component(position_type, mover_id);
    Box_Collider *mover_collider = get_component(box_collider_type, mover_id);
    Grid_Collider *grid_collider = get_component(grid_collider_type, grid_collider_id);

    Collision_Info collision_info;
    collision_info.modified_move_x = 0;
    collision_info.modified_move_y = move_y;

    int top_right_x = mover_position->x + mover_collider->w;
    int top_right_y = mover_position->y;
    int top_left_x = mover_position->x;
    int top_left_y = top_right_y;
    int bot_right_x = top_right_x;
    int bot_right_y = mover_position->y + mover_collider->h;

    int move_x_sign = sign(move_x);
    int abs_move_x = abs(move_x);
    int move_y_sign = sign(move_y);
    int abs_move_y = abs(move_y);

    if(move_x > 0)
    {
        int grid_x = get_grid_x(top_right_x, grid_collider);
        int right_vertical_position = (grid_x + 1) * grid_collider->cell_width;
        // X movement from start to first vertical intersection.
        int delta_x_0 = right_vertical_position - top_right_x;
        // X movement per vertical intersection.
        int delta_x = grid_collider->cell_width;
        
        if(abs_move_x < delta_x_0)
        {
            collision_info.modified_move_x = move_x;
        }
        else
        {
            int vertical_intersections = 1 + (int)floor(
                (double)(abs_move_x - delta_x_0) / 
                (double)grid_collider->cell_width
            );

            // Percentage of total movement per vertical intersection.
            double movement_ratio = (double)grid_collider->cell_width / (double)move_x;
            // Y movement per vertical intersection.
            int delta_y = (int)(movement_ratio * (double)move_y);
            // Percentage of total movement from start to first vertical intersection.
            double movement_ratio_0 = (double)delta_x_0 / (double)move_x;
            // Y movement from start to first vertical intersection.
            int delta_y_0 = (int)(movement_ratio_0 * (double)move_y) ;

            printf("Vertical intersections: %d\n", vertical_intersections);

            int non_collision_intersections = 0;

            for(int i = 0; i < vertical_intersections; i++)
            {
                int total_delta_x = delta_x_0 + delta_x * i;
                int total_delta_y = delta_y_0 + delta_y * i;
                int top_right_id = position_to_grid_id(
                    top_right_x + total_delta_x, 
                    top_right_y + total_delta_y, 
                    grid_collider
                );
                int bot_right_id = position_to_grid_id(
                    bot_right_x + total_delta_x,
                    bot_right_y + total_delta_y,
                    grid_collider
                );
                
                if(grid_collider->collision_ids[top_right_id]
                    || grid_collider->collision_ids[bot_right_id])
                {
                    break;
                }
                non_collision_intersections = i + 1;
            }

            printf("Non collision intersections: %d\n", non_collision_intersections);

            collision_info.modified_move_x = 
                delta_x_0 - 1
                + non_collision_intersections
                * grid_collider->cell_width;
        }
    }
    else if(move_x < 0)
    {
        int grid_x = get_grid_x(top_left_x, grid_collider);
        int left_vertical_position = grid_x * grid_collider->cell_width;
        int distance_to_nearest_vertical = top_left_x - left_vertical_position; 
        printf("Distance to nearest: %d\n", distance_to_nearest_vertical);

        if(abs_move_x < distance_to_nearest_vertical)
        {
            collision_info.modified_move_x = move_x;
        }
        else
        {
            int vertical_intersection_count = 1 + (int)floor(
                (double)(abs_move_x - distance_to_nearest_vertical) / 
                (double)grid_collider->cell_width
            );

            printf("Vertical intersections: %d\n", vertical_intersection_count);

            int non_collision_intersection_count = 0;

            printf("Grid ID: %d\n", grid_x - 1);
            printf("Left ID: %d\n", grid_collider->collision_ids[grid_x - 1]);
            for(int i = 1; i <= vertical_intersection_count; i++)
            {
                if(grid_collider->collision_ids[grid_x - i] == 1) { break; }
                non_collision_intersection_count = i;
            }

            printf("Non collision intersections: %d\n", non_collision_intersection_count);

            collision_info.modified_move_x = 
                distance_to_nearest_vertical
                + (non_collision_intersection_count)
                * grid_collider->cell_width;
            collision_info.modified_move_x *= -1;
        } 
    }
    return collision_info;
}