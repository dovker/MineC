#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "glad/glad.h"

#include <stdlib.h>
#include <stdio.h>

#include "Engine/defines.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL2 video subsystem couldn't be initialized. Error: %s\n", SDL_GetError());
        exit(1);
    }
    printf("HELOW!");
    SDL_Window* window = SDL_CreateWindow("Glad Sample",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN |
                                          SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("SDL2 Renderer couldn't be created. Error: %s\n");
        exit(1);
    }

    // Create a OpenGL context on SDL2
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    // Load GL extensions using glad
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        printf("Failed to initialize the OpenGL context.");
        exit(1);
    }

    // Loaded OpenGL successfully.
    printf("OpenGL version loaded: %d.%d\n", GLVersion.major, GLVersion.minor);

    // Create an event handler
    SDL_Event event;
    // Loop condition
    b8 running = true;

    f32 vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    }; 
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    u32 VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    u32 vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    u32 fragmentShader;
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "} \n";
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    u32 shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (running) {
        SDL_PollEvent(&event);

        switch(event.type) {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    // Destroy everything to not leak memory.
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}