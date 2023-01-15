#include "Physics.h"

bool Collided(const SDL_Point &p1, const SDL_Point &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool Collided(const SDL_Point &p, const SDL_Rect &r)
{
    return p.x >= r.x &&
           p.x <= r.x + r.w &&
           p.y >= r.y &&
           p.y <= r.y + r.h;
}
bool Collided(const SDL_Rect &r, const SDL_Point &p)
{
    return Collided(p, r);
}
bool Collided(const SDL_Rect &r1, const SDL_Rect &r2)
{
    const size_t NB_CORNERS = 4;
    SDL_Point corners[] = {{r1.x, r1.y}, {r1.x + r1.w, r1.y}, {r1.x, r1.y + r1.h}, {r1.x + r1.w, r1.y + r1.h}};

    for (size_t i = 0; i < NB_CORNERS; i++)
    {
        if (Collided(corners[i], r2))
        {
            return true;
        }
    }
    return false;
}
