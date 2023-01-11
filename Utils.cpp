#include <cstdlib>
#include "Utils.h"
int gen_random_int(int min_val, int max_val)
{
    return min_val + (std::rand() % (max_val - min_val + 1));
}
void CalculateDirection(int curr_x, int curr_y, int goal_x, int goal_y,
                        DirectionEnum *out_up_down, DirectionEnum *out_left_right)
{
    int delta_x = abs(curr_x - goal_x);
    int delta_y = abs(curr_y - goal_y);

    if (delta_x > delta_y)
    {
        if (curr_x)
            *out_up_down =
    }
}