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
    return grid_id;
}

int sign(int number)
{
    if(number > 0) { return 1; }
    if(number < 0) { return -1; }
    return 0;
}

double vector_length(int x, int y)
{
    return sqrt(pow((double)x, 2) + pow((double)y, 2));
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

Collision_Info vertical_collision(
    Grid_Collider *grid_collider, int x_0, int y_0, int move_x, int move_y, 
    int is_right_point
)
{
    // This makes RIGHT points find the correct vertical.
    int right_x_offset = 1;
    // This makes LEFT points check collision properly when moving leftwards.
    int left_x_offset = 0;
    if(!is_right_point)
    {
        // Not a RIGHT point, so offset is not needed.
        right_x_offset = 0;
        // LEFT offset is only required when moving leftwards.
        if(move_x < 0) { left_x_offset = 1; }
    }

    Collision_Info collision_info;
    int grid_x = get_grid_x(x_0 - right_x_offset, grid_collider);
    // This is the position of the nearest LEFT vertical by default.
    int nearest_vertical_position = grid_x * grid_collider->cell_width;
    // If moving to the right, add cell width to get RIGHT vertical instead.
    if(move_x > 0) { nearest_vertical_position += grid_collider->cell_width; }
    // X movement from start to first vertical intersection.
    int delta_x_0 = nearest_vertical_position - x_0;
    // X movement per vertical intersection.
    int delta_x = grid_collider->cell_width * sign(move_x);
    
    if(move_x == 0)
    {
        collision_info.modified_move_x = 0;
        collision_info.modified_move_y = move_y;
        return collision_info;
    }
    else if(abs(move_x) < abs(delta_x_0))
    {
        // Don't modify movement because there is no chance of collision.
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = move_y;
        return collision_info;
    }

    // Percentage of total movement per vertical intersection.
    double movement_ratio = (double)grid_collider->cell_width / (double)move_x;
    // Y movement per vertical intersection.
    int delta_y = (int)(movement_ratio * (double)move_y);
    // Percentage of total movement from start to first vertical intersection.
    double movement_ratio_0 = (double)delta_x_0 / (double)move_x;
    // Y movement from start to first vertical intersection.
    int delta_y_0 = (int)(movement_ratio_0 * (double)move_y);

    collision_info.modified_move_x = delta_x_0;
    collision_info.modified_move_y = delta_y_0;
    while(abs(collision_info.modified_move_x) < abs(move_x))
    {
        int grid_id = position_to_grid_id(
            x_0 + collision_info.modified_move_x - left_x_offset,
            y_0 + collision_info.modified_move_y,
            grid_collider
        );
        if(grid_collider->collision_ids[grid_id] == 1) { break; }
        collision_info.modified_move_x += delta_x;
        collision_info.modified_move_y += delta_y;
    }
    if(abs(collision_info.modified_move_x) > abs(move_x))
    {
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = move_y;
    }

    printf(
        "Modified x: %d, delta_x_0: %d\n", 
        collision_info.modified_move_x, delta_x_0
    );
    return collision_info;
}

Collision_Info horizontal_collision(
    Grid_Collider *grid_collider, int x_0, int y_0, int move_x, int move_y, 
    int is_right_point, int is_bot_point
)
{
    // Need to be checking is_bot_point and is_right_point for both
    // vertical and horizontal collision.

    // TODO: maybe rename these to intersection and collision offset.
    // This makes BOTTOM points find the correct horizontal.
    int bot_y_offset = 1;
    // This makes TOP points check collision properly when moving upwards.
    int top_y_offset = 0;
    if(!is_bot_point)
    {
        // Not a BOTTOM point, so offset is not needed.
        bot_y_offset = 0;
        // TOP offset is only required when moving upwards.
        if(move_y < 0) { top_y_offset = 1; }
    }
    // This makes RIGHT points always check collision properly.
    int right_x_offset = (is_right_point) ? 1 : 0;

    Collision_Info collision_info;
    int grid_y = get_grid_y(y_0 - bot_y_offset, grid_collider);
    // This is the position of the nearest UP horizontal by default.
    int nearest_horizontal_position = grid_y * grid_collider->cell_width;
    // If moving down, add cell height to get DOWN horizontal instead.
    if(move_y > 0) { nearest_horizontal_position += grid_collider->cell_height; }
    // Y movement from start to first horizontal intersection.
    int delta_y_0 = nearest_horizontal_position - y_0;
    // Y movement per horizontal intersection.
    int delta_y = grid_collider->cell_height * sign(move_y);
    
    if(move_y == 0)
    {
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = 0;
        return collision_info;
    }
    else if(abs(move_y) < abs(delta_y_0))
    {
        // Don't modify movement because there is no chance of collision.
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = move_y;
        return collision_info;
    }

    // Percentage of total movement per horizontal intersection.
    double movement_ratio = (double)grid_collider->cell_height / (double)move_y;
    // X movement per horizontal intersection.
    int delta_x = (int)(movement_ratio * (double)move_x);
    // Percentage of total movement from start to first horizontal intersection.
    double movement_ratio_0 = (double)delta_y_0 / (double)move_y;
    // X movement from start to first horizontal intersection.
    int delta_x_0 = (int)(movement_ratio_0 * (double)move_x);

    collision_info.modified_move_x = delta_x_0;
    collision_info.modified_move_y = delta_y_0;
    while(abs(collision_info.modified_move_y) < abs(move_y))
    {
        int grid_id = position_to_grid_id(
            x_0 + collision_info.modified_move_x - right_x_offset,
            y_0 + collision_info.modified_move_y - top_y_offset,
            grid_collider
        );
        if(grid_collider->collision_ids[grid_id] == 1) { break; }
        collision_info.modified_move_x += delta_x;
        collision_info.modified_move_y += delta_y;
    }
    if(abs(collision_info.modified_move_y) > abs(move_y))
    {
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = move_y;
    }

    printf(
        "Modified y: %d, delta_y_0: %d\n", 
        collision_info.modified_move_y, delta_y_0
    );
    return collision_info;
}

Collision_Info point_collision(
    Grid_Collider *grid_collider, int x_0, int y_0, int move_x, int move_y, 
    int is_right_point, int is_bot_point
)
{
    Collision_Info vertical = vertical_collision(
        grid_collider, x_0, y_0, move_x, move_y, is_right_point
    );
    Collision_Info horizontal = horizontal_collision(
        grid_collider, x_0, y_0, move_x, move_y, is_right_point, is_bot_point
    );

    double vertical_length = 
        vector_length(vertical.modified_move_x, vertical.modified_move_y);
    double horizontal_length =
        vector_length(horizontal.modified_move_x, horizontal.modified_move_y);

    if(vertical_length < horizontal_length) { return vertical; }
    else { return horizontal; }
    return vertical;
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
    int bot_left_x = top_left_x;
    int bot_left_y = bot_right_y;

    Collision_Info top_left_ci = 
        point_collision(grid_collider, top_left_x, top_left_y, move_x, move_y, 0, 0);
    Collision_Info top_right_ci = 
        point_collision(grid_collider, top_right_x, top_right_y, move_x, move_y, 1, 0);
    Collision_Info bot_left_ci = 
        point_collision(grid_collider, bot_left_x, bot_left_y, move_x, move_y, 0, 1);
    Collision_Info bot_right_ci =
        point_collision(grid_collider, bot_right_x, bot_right_y, move_x, move_y, 1, 1);
    if(move_x != 0 || move_y != 0) { printf("----------------\n"); }

    double top_left_length = 
        vector_length(top_left_ci.modified_move_x, top_left_ci.modified_move_y);
    double top_right_length = 
        vector_length(top_right_ci.modified_move_x, top_right_ci.modified_move_y);
    double bot_left_length = 
        vector_length(bot_left_ci.modified_move_x, bot_left_ci.modified_move_y);
    double bot_right_length = 
        vector_length(bot_right_ci.modified_move_x, bot_right_ci.modified_move_y);

    double lengths[] = 
        { top_left_length, top_right_length, bot_left_length, bot_right_length };
    int min_length_id = 0;
    for(int i = 0; i < 4; i++)
    {
        if(lengths[i] < lengths[min_length_id]) { min_length_id = i; }
    }
    if(min_length_id == 0) { return top_left_ci; }
    else if(min_length_id == 1) { return top_right_ci; }
    else if(min_length_id == 2) { return bot_left_ci; }
    else { return bot_right_ci; }
}