#include "display.h"
#include "vector.h"
bool is_running = false;
void setup(void);
void process_input(void);
void render(void);
void update(void);
int main(int argc, char **argv)
{
    is_running = initialize_window();
    setup();
    while (is_running)
    {
        process_input();
        update();
        render();
    }
    destroy_window();
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
        {
            is_running = false;
        }
        else if (event.key.keysym.sym == SDLK_UP)
        {
            y_increment -= 10;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            y_increment += 10;
        }
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            x_increment -= 10;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            x_increment += 10;
        }
        else
            fprintf(stderr, "%c Pressed\n", event.key.keysym.sym);
        break;
    }
}

void setup()
{
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void update()
{
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    // draw_rectangle_with_delta(130, 70, 100, 100, RED);
    draw_pixel(20, 20, RED);
    render_color_buffer();
    clear_color_buffer(RED & 0);
    SDL_RenderPresent(renderer);
}
