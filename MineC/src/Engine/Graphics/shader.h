#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Engine/defines.h"
#include "Engine/Graphics/graphics_common.h"

#ifdef MC_USE_OPENGL
#include "Engine/Graphics/OpenGL/ogl_defines.h"
#endif

void shader_create(Shader *shader, const char *filepath);
void shader_delete(Shader *shader);
void shader_bind(Shader *shader);
void shader_unbind();
void shader_recompile(Shader *shader);
void shader_set_uniform_buffer_binding(Shader *shader, UniformBuffer *buffer, const char *name); //Unnecessary if specifying binding in shader (OGL 4.2+)
u32 _shader_compile(const char *filepath);

#ifdef __cplusplus
}
#endif