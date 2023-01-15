#include <iostream>
#include <algorithm>
#include "Application.h"
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
        // TODO define Delay Time
        SDL_Delay(10);
    }
    Cleanup();
}
bool Application::Init()
{
    // TODO gerer que la valeur entree par l'utilisateur est bonne
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
    std::vector<size_t> deadSnakesIndexes;

    for (size_t i = 0; i < m_SnakeList.size(); i++)
    {
        m_SnakeList[i].Step();
        CheckForCollisions(i, deadSnakesIndexes);
    }

    std::sort(deadSnakesIndexes.begin(),
              deadSnakesIndexes.end(),
              std::greater<size_t>());

    for (auto index : deadSnakesIndexes)
    {
        m_SnakeList.erase(m_SnakeList.begin() + (int)index);
    }
}
void Application::CheckForCollisions(size_t index, std::vector<size_t> &deadSnakesIndexes)
{
    Snake &snake = m_SnakeList[index];
    for (size_t i = 0; i < m_SnakeList.size(); i++)
    {
        Snake &other_snake = m_SnakeList[i];
        size_t snake_size = snake.Get_CurrentSize(),
               other_snake_size = other_snake.Get_CurrentSize();

        if (other_snake.Get_Id() == snake.Get_Id() || other_snake_size == 0)
        {
            continue;
        }

        if (snake_size == 0)
        {
            break;
        }

        size_t collision_spot;

        if (!Collision(snake, other_snake, &collision_spot))
        {
            continue;
        }

        size_t new_snake_size, new_other_snake_size;
        if (collision_spot == HEAD_INDEX)
        {
            size_t id_killer, id_killed;
            if (snake_size > other_snake_size)
            {
                // TODO define pour le 60%
                new_snake_size = snake_size + other_snake_size * .6;
                new_other_snake_size = 0;
                deadSnakesIndexes.push_back(i);
                id_killer = snake.Get_Id();
                id_killed = other_snake.Get_Id();
            }
            else
            {
                // TODO define pour le 60%
                new_snake_size = 0;
                new_other_snake_size = other_snake_size + snake_size * .6;
                deadSnakesIndexes.push_back(index);
                id_killer = other_snake.Get_Id();
                id_killed = snake.Get_Id();
            }
            std::cout << id_killer << " killed "
                      << id_killed << std::endl;
        }
        else
        {
            // TODO define pour le 40%
            new_other_snake_size = collision_spot;
            new_snake_size = snake_size + (other_snake_size - collision_spot) * .4;
        }
        other_snake.Set_Length(new_other_snake_size);
        snake.Set_Length(new_snake_size);
    }
}
void Application::Render()
{
    // Set background color
    // TODO define pour la couleur
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
    for (int i = 0; i < nb_snakes; i++)
    {

        int x = gen_random_int(0, m_WindowWidth - 1);
        int y = gen_random_int(0, m_WindowHeight - 1);
        int apple_x = gen_random_int(0, m_WindowWidth - 1);
        int apple_y = gen_random_int(0, m_WindowHeight - 1);

        m_SnakeList.push_back(Snake(i,
                                    Position(x, y),
                                    Position(apple_x, apple_y),
                                    m_WindowWidth,
                                    m_WindowHeight));
    }
}
