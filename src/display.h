#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int x_increment;
extern int y_increment;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

typedef enum
{
    RED = 0xFFFF0000,
    GREEN = 0xFF00FF00,
    BLUE = 0xFF0000FF,
    WHITE = 0xFFFFFFFF
} ColorARGB;

bool initialize_window(void);
void draw_grid(int);
void draw_rectangle(int, int, int, int, uint32_t);
void draw_rectangle_with_delta(int x, int y, int width, int height, uint32_t color);
void destroy_window(void);
void clear_color_buffer(uint32_t);
void render_color_buffer(void);
void draw_pixel(int x, int y, uint32_t color);

#endif