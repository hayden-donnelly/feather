#include "camera.h"

Camera camera_init(Vec2_Int pos, SDL_Renderer *renderer)
{
    Camera new_camera;
    new_camera.pos = pos;
    new_camera.renderer = renderer;
    return new_camera;
}