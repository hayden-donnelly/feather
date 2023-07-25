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
    Grid_Collider *grid_collider, int x_0, int y_0, int move_x, int move_y
)
{
    Collision_Info collision_info;
    int grid_x = get_grid_x(x_0, grid_collider);
    // This is the position of the nearest LEFT vertical by default.
    int nearest_vertical_position = grid_x * grid_collider->cell_width;
    // If moving to the right, add cell width to get RIGHT vertical instead.
    if(move_x > 0) { nearest_vertical_position += grid_collider->cell_width; }
    // X movement from start to first vertical intersection.
    int delta_x_0 = nearest_vertical_position - x_0;
    // X movement per vertical intersection.
    int delta_x = grid_collider->cell_width * sign(move_x);
    int offset = -sign(move_x);
    
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
            x_0 + collision_info.modified_move_x,
            y_0 + collision_info.modified_move_y,
            grid_collider
        );
        if(grid_collider->collision_ids[grid_id] == 1) { break; }
        collision_info.modified_move_x += delta_x;
        collision_info.modified_move_x += delta_y;
    }
    if(abs(collision_info.modified_move_x) > abs(move_x))
    {
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = move_y;
    }
    collision_info.modified_move_x += offset;

    printf(
        "Modified x: %d, delta_x_0: %d\n", 
        collision_info.modified_move_x, delta_x_0
    );
    return collision_info;
}

Collision_Info horizontal_collision(
    Grid_Collider *grid_collider, int x_0, int y_0, int move_x, int move_y
)
{
    Collision_Info collision_info;
    int grid_y = get_grid_y(y_0, grid_collider);
    // This is the position of the nearest UP horizontal by default.
    int nearest_horizontal_position = grid_y * grid_collider->cell_height;
    // If moving down, add cell height to get DOWN vertical instead.
    if(move_y > 0) { nearest_horizontal_position += grid_collider->cell_height; }
    // Y movement from start to first horizontal intersection.
    int delta_y_0 = nearest_horizontal_position - y_0;
    // Y movement per vertical intersection.
    int delta_y = grid_collider->cell_height;
    int offset = -sign(move_y);

    if(abs(move_y) <= abs(delta_y_0))
    {
        // Don't modify movement because there is no chance of collision.
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = move_y;
        return collision_info;
    }

    int max_horizontal_intersections = 1 + (int)floor(
        (double)(abs(move_y) - delta_y_0) / 
        (double)grid_collider->cell_height
    );

    // Percentage of total movement per horizontal intersection.
    double movement_ratio = (double)grid_collider->cell_height / (double)move_y;
    // X movement per horizontal intersection.
    int delta_x = (int)(movement_ratio * (double)move_x);
    // Percentage of total movement from start to first horizontal intersection.
    double movement_ratio_0 = (double)delta_y_0 / (double)move_y;
    // X movement from start to first horizontal intersection.
    int delta_x_0 = (int)(movement_ratio_0 * (double)move_x);

    int non_collision_intersections = 0;
    for(int i = 0; i < max_horizontal_intersections; i++)
    {
        int grid_id = position_to_grid_id(
            x_0 + delta_x_0 + delta_x * i, 
            y_0 + delta_y_0 + delta_y * i, 
            grid_collider
        );

        if(grid_collider->collision_ids[grid_id]) { break; }
        non_collision_intersections = i + 1;
    }

    if(non_collision_intersections == max_horizontal_intersections)
    {
        // Don't modify movement because there were no collisions.
        collision_info.modified_move_x = move_x;
        collision_info.modified_move_y = move_y;
    }
    else
    {
        // Decrease movement so it ends at the edge of the collision.
        collision_info.modified_move_x = 
            delta_x_0 + non_collision_intersections * delta_x;
        collision_info.modified_move_y = 
            delta_y_0 + non_collision_intersections * delta_y + offset;
    }
    return collision_info;
}

Collision_Info point_collision(
    Grid_Collider *grid_collider, int x_0, int y_0, int move_x, int move_y
)
{
    Collision_Info vertical = 
        vertical_collision(grid_collider, x_0, y_0, move_x, move_y);
    Collision_Info horizontal = 
        horizontal_collision(grid_collider, x_0, y_0, move_x, move_y);

    double vertical_length = 
        vector_length(vertical.modified_move_x, vertical.modified_move_y);
    double horizontal_length =
        vector_length(horizontal.modified_move_x, horizontal.modified_move_y);

    //if(vertical_length < horizontal_length) { return vertical; }
    //else { return horizontal; }
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
        point_collision(grid_collider, top_left_x, top_left_y, move_x, move_y);
    Collision_Info top_right_ci = 
        point_collision(grid_collider, top_right_x, top_right_y, move_x, move_y);
    Collision_Info bot_left_ci = 
        point_collision(grid_collider, bot_left_x, bot_left_y, move_x, move_y);
    Collision_Info bot_right_ci =
        point_collision(grid_collider, bot_right_x, bot_right_y, move_x, move_y);
    if(move_x != 0) { printf("----------------\n"); }

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