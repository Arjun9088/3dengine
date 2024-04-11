#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool is_running = false;
bool initialize_window(void);
void process_input(void);
void update(void);
void render(void);
void setup(void);
int main()
{
    is_running = initialize_window();
    setup();
    while (is_running)
    {
        process_input();
        update();
        render();
    }
    return 0;
}

bool initialize_window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error Initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800,
                              600,
                              SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        fprintf(stderr, "Error creating SDL Window\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer\n");
        return false;
    }
    return true;
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        break;
    }
}

void setup()
{
}

void update()
{
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}