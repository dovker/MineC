#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Engine/defines.h"
#include "Engine/Graphics/graphics_common.h"

#ifdef MC_USE_OPENGL
#include "Engine/Graphics/OpenGL/ogl_defines.h"
#endif

void uniform_buffer_create(UniformBuffer *buffer, u32 size, u32 binding);
void uniform_buffer_delete(UniformBuffer *buffer);
void uniform_buffer_set_data(UniformBuffer *buffer, void* data, u32 size, u32 offset);

#ifdef __cplusplus
}
#endif