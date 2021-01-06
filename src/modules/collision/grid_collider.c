#include <stdlib.h>
#include "grid_collider.h"

Collision_Info grid_collision(Component_Type *grid_collider, Component_Type *position, 
                                Box_Collider *box_collider, int move_x, int move_y)
{
    Collision_Info collision_info;
    collision_info.modified_move_x = 0;
    collision_info.modified_move_y = 0;

    // Greater of the two movement vectors
    int *greater_move_pointer;
    int greater_move_abs = 0;
    int greater_move_sign = 0;
    int greater_move_step = 0;
    int greater_move_step_remainder = 0;
    int greater_directional_offset = 0;
    int greater_variable_offset_1 = 0;
    int greater_variable_offset_2 = 0;
    int greater_multiplier = 0;
    int greater_target_axis = 0;
    int greater_target_cell_dimension = 0;

    // Lesser of the two movement vectors
    int *lesser_move_pointer;
    int lesser_move_abs = 0;
    int lesser_move_sign = 0;
    int lesser_move_step = 0;
    int lesser_directional_offset = 0;
    int lesser_variable_offset_1 = 0;
    int lesser_variable_offset_2 = 0;
    int lesser_multiplier = 0;
    int lesser_target_axis = 0;
    int lesser_target_cell_dimension = 0;

    for(int i = 0; i < grid_collider->real_length; i++)
    {
        Grid_Collider *target = grid_collider->data[i];
        Position *target_pos = get_component(position, target->entity_id);

        // Differentiate lesser and greater move
        // This can be made more efficient
        int abs_move_x = abs(move_x);
        int abs_move_y = abs(move_y);
        if(abs_move_x > abs_move_y)
        {
            // Greater values assignment
            greater_move_pointer = &collision_info.modified_move_x;
            greater_move_abs = abs_move_x;
            greater_move_sign = (int)copysign(1, move_x);
            greater_directional_offset = (greater_move_sign > 0) ? box_collider->x + box_collider->w : box_collider->x;
            greater_variable_offset_1 = box_collider->x;
            greater_variable_offset_2 = box_collider->x + box_collider->w;
            greater_multiplier = 1;
            greater_target_axis = target_pos->x;
            greater_target_cell_dimension = target->cell_width;

            // Lesser values assignment
            lesser_move_pointer = &collision_info.modified_move_y;
            lesser_move_abs = abs_move_y;
            lesser_move_sign = (int)copysign(1, move_y);
            lesser_directional_offset = (lesser_move_sign < 0) ? box_collider->y + box_collider->h : box_collider->y;
            lesser_variable_offset_1 = box_collider->y;
            lesser_variable_offset_2 = box_collider->y = box_collider->h;
            lesser_multiplier = target->grid_width;
            lesser_target_axis = target_pos->y;
            lesser_target_cell_dimension = target->cell_height;
        }
        else
        {
            // Greater values assignment
            greater_move_pointer = &collision_info.modified_move_y;
            greater_move_abs = abs_move_y;
            greater_move_sign = (int)copysign(1, move_y);
            greater_directional_offset = (greater_move_sign < 0) ? box_collider->y + box_collider->h : box_collider->y;
            greater_variable_offset_1 = box_collider->y;
            greater_variable_offset_2 = box_collider->y + box_collider->h;
            greater_multiplier = target->grid_width;
            greater_target_axis = target_pos->y;
            greater_target_cell_dimension = target->cell_height;

            // Lesser values assignment
            lesser_move_pointer = &collision_info.modified_move_x;
            lesser_move_abs = abs_move_x;
            lesser_move_sign = (int)copysign(1, move_x);
            lesser_directional_offset = (lesser_move_sign > 0) ? box_collider->x + box_collider->w : box_collider->x;
            lesser_variable_offset_1 = box_collider->x;
            lesser_variable_offset_2 = box_collider->x = box_collider->w;
            lesser_multiplier = 1;
            lesser_target_axis = target_pos->x;
            lesser_target_cell_dimension = target->cell_width;
        }

        // Find approproate x y movement steps
        if(greater_move_abs != 0)
        {
            if(lesser_move_abs != 0)
            {
                // Both moves are non-zero
                greater_move_step = (greater_move_abs + lesser_move_abs - 1) / lesser_move_abs;
                greater_move_step_remainder = greater_move_abs - greater_move_abs / greater_move_step * greater_move_step;
                lesser_move_step = 1;
            }
            else
            {
                // Only one move is non-zero
                greater_move_step_remainder = greater_move_abs;
                lesser_move_step = 0;
            }
        }
        else
        {
            // Both moves are zero
            return collision_info;
        }

        // Check collision on main body of move
        int col_id_1 = 0;
        int col_id_2 = 0;
        for(int i = 0; i < lesser_move_abs; i++)
        {
            for(int g = 0; g < greater_move_step; g++)
            {
                // TODO: test move pointer
                col_id_1 = target->collision_ids[(lesser_variable_offset_1 + *lesser_move_pointer - lesser_target_axis) 
                                                / lesser_target_cell_dimension * lesser_multiplier
                                                + (greater_directional_offset + *greater_move_pointer - greater_target_axis)
                                                / greater_target_cell_dimension * greater_multiplier];
                col_id_2 = target->collision_ids[(lesser_variable_offset_2 + *lesser_move_pointer - lesser_target_axis) 
                                                / lesser_target_cell_dimension * lesser_multiplier
                                                + (greater_directional_offset + *greater_move_pointer - greater_target_axis)
                                                / greater_target_cell_dimension * greater_multiplier];
                if(col_id_1 != 0 || col_id_2 != 0)
                {
                    greater_move_step = 0;
                    greater_move_step_remainder = 0;
                    break;
                }
                *greater_move_pointer += 1 * greater_move_sign;
            }
            for(int l = 0; l < lesser_move_step; l++)
            {
                col_id_1 = target->collision_ids[(lesser_directional_offset + *lesser_move_pointer - lesser_target_axis) 
                                                / lesser_target_cell_dimension * lesser_multiplier
                                                + (greater_variable_offset_1 + *greater_move_pointer - greater_target_axis)
                                                / greater_target_cell_dimension * greater_multiplier];
                col_id_2 = target->collision_ids[(lesser_directional_offset + *lesser_move_pointer - lesser_target_axis) 
                                                / lesser_target_cell_dimension * lesser_multiplier
                                                + (greater_variable_offset_2 + *greater_move_pointer - greater_target_axis)
                                                / greater_target_cell_dimension * greater_multiplier];
                if(col_id_1 != 0 || col_id_2 != 0)
                {
                    lesser_move_step = 0;
                    break;
                }
                *lesser_move_pointer += 1 * lesser_move_sign;
            }
        }

        // Check collision on remainder of move
        for(int gr = 0; gr < greater_move_step_remainder; gr++)
        {
            col_id_1 = target->collision_ids[(lesser_variable_offset_1 + *lesser_move_pointer - lesser_target_axis) 
                        / lesser_target_cell_dimension * lesser_multiplier
                        + (greater_directional_offset + *greater_move_pointer - greater_target_axis)
                        / greater_target_cell_dimension * greater_multiplier];
            col_id_2 = target->collision_ids[(lesser_variable_offset_2 + *lesser_move_pointer - lesser_target_axis) 
                        / lesser_target_cell_dimension * lesser_multiplier
                        + (greater_directional_offset + *greater_move_pointer - greater_target_axis)
                        / greater_target_cell_dimension * greater_multiplier];
            if(col_id_1 != 0 || col_id_2 != 0)
            {
                greater_move_step_remainder = 0;
                break;
            }
            *greater_move_pointer += 1 * greater_move_sign;
        }
        for(int l = 0; l < lesser_move_step; l++)
        {
            col_id_1 = target->collision_ids[(lesser_directional_offset + *lesser_move_pointer - lesser_target_axis) 
                        / lesser_target_cell_dimension * lesser_multiplier
                        + (greater_variable_offset_1 + *greater_move_pointer - greater_target_axis)
                        / greater_target_cell_dimension * greater_multiplier];
            col_id_2 = target->collision_ids[(lesser_directional_offset + *lesser_move_pointer - lesser_target_axis) 
                        / lesser_target_cell_dimension * lesser_multiplier
                        + (greater_variable_offset_2 + *greater_move_pointer - greater_target_axis)
                        / greater_target_cell_dimension * greater_multiplier];
            if(col_id_1 != 0 || col_id_2 != 0)
            {
                lesser_move_step = 0;
                break;
            }
            *lesser_move_pointer += 1 * lesser_move_sign;
        }

        //*lesser_move_pointer = 10;
        move_x = collision_info.modified_move_x;
        move_y = collision_info.modified_move_y;
    }

    return collision_info;
}