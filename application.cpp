#include "application.h"
#include <iostream>
#include "Utils.h"
#include "Position.h"
Application::Application() : m_Running(false), m_SnakeList(std::vector<Snake>())
{
}
void Application::Execute()
{
    m_Running = Init();

    while (m_Running)
    {
        HandleEvents();
        RunLogic();
        Render();
        SDL_Delay(10);
    }
    Cleanup();
}
bool Application::Init()
{
    int nb_snakes;
    std::cout << "ce programme ..." << std::endl;
    std::cout << "largeur [50..1200] : ";
    std::cin >> m_WindowWidth;
    std::cout << "hauteur [50..800] : ";
    std::cin >> m_WindowHeight;
    std::cout << "nbre snakes [2..1000] : ";
    std::cin >> nb_snakes;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize SDL" << std::endl;

        return false;
    }

    if ((m_Window = SDL_CreateWindow(m_AppName,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     m_WindowWidth,
                                     m_WindowHeight,
                                     0)) == nullptr)
    {
        std::cout << "Failed to initialize SDL Window" << std::endl;

        return false;
    }

    if ((m_Renderer = SDL_CreateRenderer(m_Window, -1, 0)) == nullptr)
    {
        std::cout << "Failed to initialize SDL Renderer" << std::endl;

        return false;
    }
    GenerateSnakes(nb_snakes);
    return true;
}
void Application::OnEvent(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        m_Running = false;
        break;
    default:
        // Unhandled event
        break;
    }
}
void Application::RunLogic()
{
    for (auto &snake : m_SnakeList)
    {
        snake.Step();
    }
}
void Application::Render()
{
    // Set background color
    SDL_SetRenderDrawColor(m_Renderer, 0x7F, 0x7F, 0x7F, 0xFF);
    SDL_RenderClear(m_Renderer);
    for (auto &snake : m_SnakeList)
    {
        snake.Draw(m_Renderer);
    }
    SDL_RenderPresent(m_Renderer);
}
void Application::Cleanup()
{
    SDL_Quit();
}

void Application::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        OnEvent(&event);
    }
}
void Application::GenerateSnakes(int nb_snakes)
{

    // make sure we don't spawn a snake in the border of the board
    int min_val = SNAKE_DEFAULT_LENGTH * 4;
    int max_x = m_WindowWidth - min_val;
    int max_y = m_WindowHeight - min_val;

    for (int i = 0; i < nb_snakes; i++)
    {

        int x = gen_random_int(min_val, max_x);
        int y = gen_random_int(min_val, max_y);
        int apple_x = gen_random_int(0, m_WindowWidth);
        int apple_y = gen_random_int(0, m_WindowHeight);

        m_SnakeList.push_back(Snake(Position(x, y),
                                    Position(apple_x, apple_y),
                                    m_WindowWidth,
                                    m_WindowHeight));
    }
}