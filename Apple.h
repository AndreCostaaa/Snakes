#include "Position.h"
#include "SDL2/SDL.h"
#ifndef APPLE_H
#define APPLE_H
#define APPLE_WIDTH_HEIGHT 2

class Apple
{
public:
    Apple(const Position &start_pos);
    void Draw(SDL_Renderer *renderer);
    int Get_X();
    int Get_Y();
    bool is_eaten();
    void Set_Eaten();
    int Get_Value();

private:
    SDL_Rect m_Body;
    bool m_IsEaten;
    int m_Value;
};

#endif