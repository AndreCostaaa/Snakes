#ifndef APPLICATION_H
#define APPLICATION_H
#include <SDL2/SDL.h>
#include <vector>
#include "Snake.h"

class Application
{
public:
    Application();
    void Execute();

private:
    bool m_Running;
    const char *m_AppName = "Snakes";
    SDL_Window *m_Window = nullptr;
    SDL_Renderer *m_Renderer = nullptr;
    std::vector<Snake> m_SnakeList;
    int m_WindowWidth;
    int m_WindowHeight;

private:
    bool Init();
    void RunLogic();
    void Render();
    void Cleanup();
    void HandleEvents();
    void OnEvent(SDL_Event *event);
    void GenerateSnakes(int nb_snakes);
    void CheckForCollisions(size_t index, std::vector<size_t> &deadSnakesIndexes);
};

#endif