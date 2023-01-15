#include "SDL2/SDL_rect.h"
#ifndef PHYSICS_H
#define PHYSICS_H

bool Collided(const SDL_Point &p1, const SDL_Point &p2);
bool Collided(const SDL_Rect &r1, const SDL_Rect &r2);
bool Collided(const SDL_Point &p, const SDL_Rect &r);
bool Collided(const SDL_Rect &r, const SDL_Point &p);
#endif