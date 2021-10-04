#ifdef MC_USE_SDL2

#include <stdlib.h>
#include <stdio.h>

#include "Engine/Window/window.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"

void window_create(McWindow *window, const char* title, u32 width, u32 height)
{
    window->title = title;
    window->width = width;
    window->height = height;
    window->fullscreen = false;
    window->running = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL2 video subsystem couldn't be initialized. Error: %s\n", SDL_GetError());
        exit(1);
    }

    window->window_handle = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height, SDL_WINDOW_SHOWN |
                                          SDL_WINDOW_OPENGL);


    _create_graphics_context(window);

    window_toggle_vsync(true);
}

void window_destroy(McWindow *window)
{
    _destroy_graphics_context(window);
    SDL_DestroyWindow(window->window_handle);

    SDL_Quit();
}

void window_update(McWindow *window)
{
    _poll_events(window);
    _swap_graphics_buffers(window);
}

void window_change_title(McWindow *window, const char* title)
{
    SDL_SetWindowTitle(window->window_handle, title);
}

u32 window_get_time()
{
    return SDL_GetTicks();
}

void window_toggle_vsync(b8 toggle)
{
    _set_graphics_swap_interval(toggle);
}

void window_toggle_fulscreen(McWindow* window, b8 toggle)
{
    if(window->fullscreen != toggle)
    {
        window->fullscreen = toggle;
        SDL_SetWindowFullscreen(window->window_handle, toggle);
        //SDL_ShowCursor(currentState);
    }
}

void _poll_events(McWindow* window)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type) {
        case SDL_QUIT:
            window->running = false;
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
                window->running = false;
                break;
            }
        }
    }
}

#endif