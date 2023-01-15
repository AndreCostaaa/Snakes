#include <cstdlib>
#include "Utils.h"
int gen_random_int(int min_val, int max_val)
{
    return min_val + (std::rand() % (max_val - min_val + 1));
}
void CalculateDirectionPriority(int curr_x, int curr_y, int goal_x, int goal_y,
                                DirectionEnum *directions_buf)
{
    int delta_x = abs(curr_x - goal_x);
    int delta_y = abs(curr_y - goal_y);

    if (delta_x == 0 && delta_y == 0)
    {
        *directions_buf = None;
        return;
    }
    bool goUp = curr_y > goal_y;
    bool goLeft = curr_x > goal_x;

    if (delta_x >= delta_y) // gotta move in the x axis
    {
        directions_buf[0] = goLeft ? East : West;
        directions_buf[1] = goUp ? North : South;
        directions_buf[2] = goUp ? South : North;
        directions_buf[3] = goLeft ? West : East;
    }
    else
    {
        directions_buf[0] = goUp ? North : South;
        directions_buf[1] = goLeft ? East : West;
        directions_buf[2] = goLeft ? West : East;
        directions_buf[3] = goUp ? South : North;
    }
}