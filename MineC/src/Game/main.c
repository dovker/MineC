#include <stdlib.h>
#include <stdio.h>

#include "Engine/defines.h"
#include "Engine/Window/window.h"

#include "Engine/Containers/dynamic_array.h"

#include "Engine/Graphics/API.h"
#include "Engine/Graphics/buffer.h"
#include "Engine/Graphics/vertex_array.h"
#include "Engine/Graphics/shader.h"
#include "Engine/Graphics/uniform_buffer.h"

#include "cglm/cglm.h"
#include "cglm/cam.h"

typedef struct MC_Uniform
{
    mat4 projection;
    mat4 view;
} MC_Uniform;

int main() {
        
    McWindow window;
    window_create(&window, "Haha Poggers", 800, 600);

    graphics_init();

    f32 vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    }; 
    u32 indices[] =
    {
        0, 1, 2
    };

    VertexBuffer vert_buffer;
    vertex_buffer_create(&vert_buffer, vertices, sizeof(vertices));
    vertex_buffer_set_layout(&vert_buffer, buffer_layout_create(1, MC_FLOAT3));
    
    IndexBuffer ind_buffer;
    index_buffer_create(&ind_buffer, indices, 3);

    VertexArray vert_array;
    vertex_array_create(&vert_array);
    vertex_array_add_vertex_buffer(&vert_array, &vert_buffer);
    vertex_array_add_index_buffer(&vert_array, &ind_buffer);

    UniformBuffer uniformBuffer;
    uniform_buffer_create(&uniformBuffer, sizeof(MC_Uniform), 0);

    Shader shader;

    shader_create(&shader, "../../MineC/shaders/main.glsl");
    shader_set_uniform_buffer_binding(&shader, &uniformBuffer, "Camera");

    vec3 up = { 0.0f, 1.0f, 0.0f };

    vec3 camPos = { 0.0f, 0.0f, 1.0f };
    vec3 camTarget = { 0.0f, 0.0f, 0.0f };

    MC_Uniform uniform;

    glm_lookat(camPos, camTarget, up, uniform.view);
    glm_perspective(glm_rad(60.0f), 800.0f/600.0f, 0.01f, 1000.0f, uniform.projection);

    uniform_buffer_set_data(&uniformBuffer, &uniform, sizeof(MC_Uniform), 0);

    while (window.running) {
        
        graphics_set_clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        graphics_clear();

        shader_bind(&shader);
        vertex_array_bind(&vert_array);
        graphics_draw_indexed(&vert_array);

        window_update(&window);
    }

    vertex_buffer_delete(&vert_buffer);
    index_buffer_delete(&ind_buffer);
    vertex_array_delete(&vert_array);
    shader_delete(&shader);
    uniform_buffer_delete(&uniformBuffer);

    window_destroy(&window);
    
    return 0;
}