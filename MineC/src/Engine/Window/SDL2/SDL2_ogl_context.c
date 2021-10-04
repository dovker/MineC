#if defined(MC_USE_OPENGL) && defined(MC_USE_SDL2)

#include "Engine/Window/window.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "glad/glad.h"


void _create_graphics_context(McWindow *window)
{
    // Create a OpenGL context on SDL2
    window->gl_context = SDL_GL_CreateContext(window->window_handle);

    // Load GL extensions using glad
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        printf("Failed to initialize the OpenGL context.");
        exit(1);
    }

    // Loaded OpenGL successfully.
    printf("OpenGL version loaded: %d.%d\n", GLVersion.major, GLVersion.minor);
}
void _destroy_graphics_context(McWindow *window)
{
    SDL_GL_DeleteContext(window->gl_context);
}
void _set_graphics_swap_interval(b8 toggle)
{
    SDL_GL_SetSwapInterval(toggle);
}
void _swap_graphics_buffers(McWindow *window)
{
    SDL_GL_SwapWindow(window->window_handle);
}

#endif