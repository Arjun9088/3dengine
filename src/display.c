#include "display.h"
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
int x_increment = 0;
int y_increment = 0;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool initialize_window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error Initializing SDL.\n");
        return false;
    }
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    WINDOW_HEIGHT = display_mode.h;
    WINDOW_WIDTH = display_mode.w;
    window = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
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
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    return true;
}

void destroy_window()
{
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void clear_color_buffer(uint32_t color)
{
    for (int i = 0; i < WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH; j++)
        {
            color_buffer[(WINDOW_WIDTH * i) + j] = color;
        }
    }
}

void render_color_buffer()
{
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)sizeof(uint32_t) * WINDOW_WIDTH);
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void draw_grid(int offset)
{
    uint32_t color = WHITE;
    for (int i = 0; i < WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH; j++)
        {
            if (i % 10 == 0 || j % 10 == 0)
            {
                color_buffer[(WINDOW_WIDTH * i) + j] = color;
            }
        }
    }
}

/// @brief Draws a rectangle at a specified x and y location
/// @param x top left corner x value
/// @param y top left corner y value
/// @param width width of the rectangle
/// @param height height of the rectangle
/// @param color fill color of the rectangle
void draw_rectangle(int x, int y, int width, int height, uint32_t color)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int current_x = x + i;
            int current_y = y + j;
            color_buffer[(WINDOW_WIDTH * current_y) + current_x] = color;
        }
    }
}

void draw_rectangle_with_delta(int x, int y, int width, int height, uint32_t color)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int current_x = x + x_increment + i;
            int current_y = y + y_increment + j;
            color_buffer[(WINDOW_WIDTH * current_y) + current_x] = color;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color)
{
    if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
    {
        color_buffer[(WINDOW_WIDTH * y) + x] = color;
    }
}