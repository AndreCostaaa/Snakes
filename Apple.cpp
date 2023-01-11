#include "Apple.h"
#include "Utils.h"
Apple::Apple(const Position &position) : m_Body({position.x,
                                                 position.y,
                                                 APPLE_WIDTH_HEIGHT,
                                                 APPLE_WIDTH_HEIGHT}),
                                         m_Value(gen_random_int(1, 10)),
                                         m_IsEaten(false)
{
}

void Apple::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 175, 0, 0, 255);
    SDL_RenderFillRect(renderer, &m_Body);
}
int Apple::Get_X()
{
    return m_Body.x;
}
int Apple::Get_Y()
{
    return m_Body.y;
}

bool Apple::is_eaten()
{
    return m_IsEaten;
}
void Apple::Set_Eaten()
{
    m_IsEaten = true;
}
int Apple::Get_Value()
{
    return m_Value;
}