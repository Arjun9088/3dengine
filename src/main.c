#include "display.h"
#include "vector.h"
#define N_POINTS (9 * 9 * 9)
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
vec2_t line_endpoints[2] = {
    {0.0, 0.0},
    {0.0, 0.0}};
int first = 0;
bool is_running = false;
void setup(void);
void process_input(void);
void render(void);
void update(void);
vec3_t camera_position = {0, 0, -3};
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
            camera_position.z -= 1;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            camera_position.z += 1;
        }
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            camera_position.x -= 1;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            camera_position.x += 1;
        }
        else
            fprintf(stderr, "%c Pressed\n", event.key.keysym.sym);
        break;
    case SDL_MOUSEBUTTONDOWN:
        vec2_t pos = {event.button.x, event.button.y};
        if (!first)
        {
            first++;
            line_endpoints[0] = pos;
            line_endpoints[1] = pos;
        }
        else
        {
            line_endpoints[0] = line_endpoints[1];
            line_endpoints[1] = pos;
            fprintf(stderr, "0 index is: (%f, %f)\n", line_endpoints[0].x, line_endpoints[0].y);
            fprintf(stderr, "1 index is: (%f, %f)\n", line_endpoints[1].x, line_endpoints[1].y);
        }
        break;
    }
}

void setup()
{
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    int k = 0;
    for (float x = -1; x <= 1; x += .25)
    {
        for (float y = -1; y <= 1; y += .25)
        {
            for (float z = -1; z <= 1; z += .25)
            {
                vec3_t new_point = {x, y, z};
                cube_points[k++] = new_point;
            }
        }
    }
}

void update()
{
    for (int i = 0; i < N_POINTS; i++)
    {
        vec3_t point = cube_points[i];
        point.z -= camera_position.z;
        vec2_t projected_point = project(point);
        projected_points[i] = projected_point;
    }
}

void render()
{
    draw_grid(10);
    for (int i = 0; i < N_POINTS; i++)
    {
        vec2_t projected_point = projected_points[i];
        draw_rectangle(
            projected_point.x + (WINDOW_WIDTH / 2),
            projected_point.y + (WINDOW_HEIGHT / 2),
            4,
            4,
            BLUE);
    }
    render_color_buffer();
    clear_color_buffer(0xFF000000);
    SDL_RenderPresent(renderer);
}
