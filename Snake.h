#ifndef SNAKE_H
#define SNAKE_H

#include "Position.h"
#include "Apple.h"
#include "SDL2/SDL.h"
#include "Utils.h"
#include <vector>

#define SNAKE_DEFAULT_LENGTH 10
#define SNAKE_BODY_WIDTH 1
#define HEAD_INDEX 0

class Snake
{
    friend bool Collision(const Snake &snake, const Snake &other_snake, size_t *collision_spot);

public:
    Snake(int id, const Position &snake_start_pos,
          const Position &apple_start_pos,
          int max_x,
          int max_y);
    void Draw(SDL_Renderer *renderer);
    void Step();
    void Set_Apple(const Position &apple_pos);
    bool Is_AppleEaten();
    size_t Get_CurrentSize();
    size_t Get_Id();
    void Set_Length(size_t size);

private:
    size_t m_Length, m_MaxX, m_MaxY;
    size_t m_Id;
    Apple m_Apple;
    Position m_Position;
    std::vector<SDL_Point> m_Body;
    bool m_AteApple;

private:
    SDL_Point GetNewHead(DirectionEnum direction);
    bool CheckDirection(DirectionEnum direction);
};
#endif