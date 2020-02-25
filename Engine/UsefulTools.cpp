#include "UsefulTools.hpp"

bool MouseCollision(vector2 object_pos_max, vector2 object_pos_min, vector2 mouse_pos)
{
    if (mouse_pos.x < object_pos_max.x && mouse_pos.x > object_pos_min.x
        && mouse_pos.y < object_pos_max.y && mouse_pos.y > object_pos_min.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
