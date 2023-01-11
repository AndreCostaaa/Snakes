#include "Snake.h"
#include "Utils.h"
#include <iostream>
Snake::Snake(const Position &snake_start_pos,
             const Position &apple_start_pos,
             int max_x,
             int max_y) : m_Apple({apple_start_pos}),
                          m_Length(SNAKE_DEFAULT_LENGTH),
                          m_Body(std::vector<SDL_Rect>()),
                          m_MaxX(max_x),
                          m_MaxY(max_y)

{
    for (int i = 0; i < m_Length; i++)
    {
        SDL_Rect rect;
        rect.x = snake_start_pos.x - i * SNAKE_BODY_WIDTH;
        rect.y = snake_start_pos.y;
        rect.w = SNAKE_BODY_WIDTH;
        rect.h = SNAKE_BODY_WIDTH;
        m_Body.push_back(rect);
    }
    std::cout << m_Length << " " << m_Body.size() << " " << (m_Body.size() == m_Length) << std::endl;
}

void Snake::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (size_t i = 0; i < m_Body.size(); i++)
    {
        SDL_RenderFillRect(renderer, &m_Body[i]);
    }
    m_Apple.Draw(renderer);
}
void Snake::Step()
{
    DirectionEnum main_dir;
    DirectionEnum sec_dir;
    int head_x = m_Body[0].x;
    int head_y = m_Body[0].y;
    int apple_x = m_Apple.Get_X();
    int apple_y = m_Apple.Get_Y();
    CalculateDirection(head_x, head_y, apple_x, apple_y, &main_dir, &sec_dir);

    if (main_dir == None && sec_dir == None) // we got an apple
    {
        m_Length += m_Apple.Get_Value();
        m_Apple = Apple({gen_random_int(0, m_MaxX),
                         gen_random_int(0, m_MaxY)});
        std::cout << "New apple" << std::endl;
        return;
    }
    SDL_Rect new_head;
    if (CheckDirection(main_dir))
    {
        new_head = GetNewHead(main_dir);
    }
    else if (CheckDirection(sec_dir))
    {
        new_head = GetNewHead(sec_dir);
    }
    else
    {
        return;
        // std::cout << "No new position to go" << std::endl;
    }
    if ((size_t)m_Length == m_Body.size())
    {
        std::cout << "pop" << std::endl;
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
    SDL_Rect new_head = GetNewHead(direction);
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

SDL_Rect Snake::GetNewHead(DirectionEnum direction)
{
    SDL_Rect new_head;
    switch (direction)
    {
    case East:
        new_head = {m_Body[HEAD_INDEX].x - SNAKE_BODY_WIDTH,
                    m_Body[HEAD_INDEX].y,
                    SNAKE_BODY_WIDTH,
                    SNAKE_BODY_WIDTH};
        break;
    case West:
        new_head = {m_Body[HEAD_INDEX].x + SNAKE_BODY_WIDTH,
                    m_Body[HEAD_INDEX].y,
                    SNAKE_BODY_WIDTH,
                    SNAKE_BODY_WIDTH};

        break;
    case North:
        new_head = {m_Body[HEAD_INDEX].x,
                    m_Body[HEAD_INDEX].y - SNAKE_BODY_WIDTH,
                    SNAKE_BODY_WIDTH,
                    SNAKE_BODY_WIDTH};
        break;
    case South:
        new_head = {m_Body[HEAD_INDEX].x,
                    m_Body[HEAD_INDEX].y + SNAKE_BODY_WIDTH,
                    SNAKE_BODY_WIDTH,
                    SNAKE_BODY_WIDTH};

        break;
    default:
        break;
    }
    return new_head;
}