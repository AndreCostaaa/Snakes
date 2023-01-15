#include "Snake.h"
#include "Utils.h"
#include "Physics.h"
#include <iostream>

#define NB_POSSIBLE_DIRECTIONS 4
Snake::Snake(int id,
             const Position &snake_start_pos,
             const Position &apple_start_pos,
             int max_x,
             int max_y) : m_Id(id),
                          m_Apple({apple_start_pos}),
                          m_Length(SNAKE_DEFAULT_LENGTH),
                          m_Body(std::vector<SDL_Point>()),
                          m_MaxX(max_x),
                          m_MaxY(max_y)

{
    m_Body.push_back({snake_start_pos.x, snake_start_pos.y});
}

void Snake::Draw(SDL_Renderer *renderer)
{
    // TODO define couleur
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderDrawPoints(renderer, &m_Body[HEAD_INDEX], m_Body.size());
    m_Apple.Draw(renderer);
}
void Snake::Step()
{
    if (m_Body.empty())
    {
        return;
    }
    DirectionEnum direction_priority_buf[NB_POSSIBLE_DIRECTIONS];

    int head_x = m_Body[HEAD_INDEX].x;
    int head_y = m_Body[HEAD_INDEX].y;
    int apple_x = m_Apple.Get_X();
    int apple_y = m_Apple.Get_Y();

    CalculateDirectionPriority(head_x, head_y, apple_x, apple_y, direction_priority_buf);

    if (direction_priority_buf[0] == None ||
        Collided(m_Body[HEAD_INDEX], m_Apple.Get_Body()))
    {
        m_Length += m_Apple.Get_Value();
        m_Apple = Apple({gen_random_int(0, m_MaxX - 1), gen_random_int(0, m_MaxY - 1)});
        return;
    }

    bool is_new_head_valid = false;
    SDL_Point new_head;
    for (int i = 0; i < NB_POSSIBLE_DIRECTIONS; i++)
    {
        if (CheckDirection(direction_priority_buf[i]))
        {
            is_new_head_valid = true;
            new_head = GetNewHead(direction_priority_buf[i]);
            break;
        }
    }

    if (!is_new_head_valid)
    {
        // TODO gerer quand elle n'a plus de direction valable
    }
    if ((size_t)m_Length == m_Body.size())
    {
        m_Body.pop_back();
    }
    m_Body.insert(m_Body.begin(), new_head);
}
void Snake::Set_Apple(const Position &apple_pos)
{
    m_Apple = Apple(apple_pos);
}

bool Snake::CheckDirection(DirectionEnum direction)
{
    if (direction == None)
    {
        return false;
    }
    SDL_Point new_head = GetNewHead(direction);
    if (new_head.x < 0 || new_head.x >= m_MaxX)
    {
        return false;
    }
    if (new_head.y < 0 || new_head.y >= m_MaxY)
    {
        return false;
    }
    for (const auto &body_part : m_Body)
    {
        if (body_part.x == new_head.x && body_part.y == new_head.y)
        {
            return false;
        }
    }
    return true;
}

size_t Snake::Get_CurrentSize()
{
    return m_Body.size();
}
SDL_Point Snake::GetNewHead(DirectionEnum direction)
{
    SDL_Point new_head;
    switch (direction)
    {
    case East:
        new_head = {m_Body[HEAD_INDEX].x - SNAKE_BODY_WIDTH,
                    m_Body[HEAD_INDEX].y};
        break;
    case West:
        new_head = {m_Body[HEAD_INDEX].x + SNAKE_BODY_WIDTH,
                    m_Body[HEAD_INDEX].y};

        break;
    case North:
        new_head = {m_Body[HEAD_INDEX].x,
                    m_Body[HEAD_INDEX].y - SNAKE_BODY_WIDTH};
        break;
    case South:
        new_head = {m_Body[HEAD_INDEX].x,
                    m_Body[HEAD_INDEX].y + SNAKE_BODY_WIDTH};

        break;
    case None:
        // should never happen
        break;
    }
    return new_head;
}

bool Collision(const Snake &snake, const Snake &other_snake, size_t *collision_spot)
{
    if (snake.m_Body.empty() || other_snake.m_Body.empty())
    {
        return false;
    }
    for (size_t i = 0; i < other_snake.m_Body.size(); i++)
    {
        if (Collided(snake.m_Body[HEAD_INDEX], other_snake.m_Body[i]))
        {
            if (collision_spot)
                *collision_spot = i;
            return true;
        }
    }
    return false;
}
void Snake::Set_Length(size_t size)
{
    m_Length = size;
    if (size > m_Length)
    {
        return;
    }
    m_Body.resize(size);
}
size_t Snake::Get_Id()
{
    return m_Id;
}