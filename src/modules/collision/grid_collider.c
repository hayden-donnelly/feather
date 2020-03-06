#include <stdlib.h>
#include "grid_collider.h"


// I'm compromising on this and only implementing collision detection/reaction for solid objects.
// This is so I can get the engine to it's first release quicker and start working on my game.
// When I have time this really needs to be re-written though.
int *grid_collision(Component_Type *grid_collider, Component_Type *position, 
                    Box_Collider *box_collider, int move_x, int move_y)
{
    int move_sign_x = (int)copysign(1, move_x);
    int move_sign_y = (int)copysign(1, move_y);

    for(int i = 0; i < grid_collider->real_length; i++)
    {
        Grid_Collider *target = grid_collider->data[i];
        Position *position = get_component(position, target->entity_id);

        int iterative_move_x;
        int iterative_move_y;

        int collision_x_done;
        int collision_y_done;
        // Which cell on the grid each of the box collider's
        // corners fall into.
        int col_grid_pos_left;
        int col_grid_pos_top;
        int col_grid_pos_right;
        int col_grid_pos_bottom;
        // I don't really need these rn but I'm leaving them in
        // for when I implement the full collision system.
        // ID corresponding to collider grid position.
        int top_left_id;
        int top_right_id;
        int bottom_left_id;
        int bottom_right_id;

        while(!collision_x_done && !collision_y_done)
        {
            if(abs(iterative_move_x) < abs(move_x) && collision_x_done)
            {
                iterative_move_x += move_sign_x;
                col_grid_pos_left = (position->x + box_collider->x + iterative_move_x) / target->cell_width;
                col_grid_pos_right = (position->x + box_collider->x + box_collider->w + iterative_move_x) / target->cell_width;
                col_grid_pos_top = (position->y + box_collider->y + iterative_move_y) / target->cell_height;
                col_grid_pos_bottom = (position->y + box_collider->y + + box_collider->h + iterative_move_y) / target->cell_height;

                if(move_sign_x < 0)
                {
                    top_left_id = target->collision_ids[col_grid_pos_top * target->grid_width + col_grid_pos_left];
                    bottom_left_id = target->collision_ids[col_grid_pos_bottom * target->grid_width + col_grid_pos_left];
                    
                    if(top_left_id != 0 || bottom_left_id != 0)
                    {
                        iterative_move_x -= move_sign_x;
                        move_x = iterative_move_x;
                        collision_x_done = 1;
                    }

                }
                else if(move_sign_x > 0)
                {
                    top_right_id = target->collision_ids[col_grid_pos_top * target->grid_width + col_grid_pos_right];
                    bottom_right_id = target->collision_ids[col_grid_pos_bottom * target->grid_width + col_grid_pos_right];

                    if(top_right_id != 0 || bottom_right_id != 0)
                    {
                        iterative_move_x -= move_sign_x;
                        move_x = iterative_move_x;
                        collision_x_done = 1;
                    }
                }
            }

            if(abs(iterative_move_y) < abs(move_y) && collision_y_done)
            {
                iterative_move_y += move_sign_y;
                col_grid_pos_left = (position->x + box_collider->x + iterative_move_x) / target->cell_width;
                col_grid_pos_right = (position->x + box_collider->x + box_collider->w + iterative_move_x) / target->cell_width;
                col_grid_pos_top = (position->y + box_collider->y + iterative_move_y) / target->cell_height;
                col_grid_pos_bottom = (position->y + box_collider->y + + box_collider->h + iterative_move_y) / target->cell_height;

                if(move_sign_y < 0)
                {
                    top_left_id = target->collision_ids[col_grid_pos_top * target->grid_width + col_grid_pos_left];
                    top_right_id = target->collision_ids[col_grid_pos_top * target->grid_width + col_grid_pos_right];
                
                    if(top_left_id != 0 || top_right_id != 0)
                    {
                        iterative_move_y -= move_sign_y;
                        move_y = iterative_move_y;
                        collision_y_done = 1;
                    }
                }
                else if(move_sign_y > 0)
                {
                    bottom_left_id = target->collision_ids[col_grid_pos_bottom * target->grid_width + col_grid_pos_left];
                    bottom_right_id = target->collision_ids[col_grid_pos_bottom * target->grid_width + col_grid_pos_right];

                    if(bottom_left_id != 0 || bottom_right_id != 0)
                    {
                        iterative_move_y -= move_sign_y;
                        move_y = iterative_move_y;
                        collision_y_done = 1;
                    }
                }
            }
        }
    }

    int modified_movement[2] = { move_x, move_y };
    return modified_movement;
}