#ifndef UTILS_H
#define UTILS_H
typedef enum
{
    None,
    North,
    East,
    South,
    West
} DirectionEnum;

int gen_random_int(int min_val, int max_val);
void CalculateDirection(int curr_x, int curr_y, int goal_x, int goal_y,
                        DirectionEnum *out_up_down, DirectionEnum *out_left_right);
#endif