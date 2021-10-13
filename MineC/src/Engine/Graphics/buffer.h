#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Engine/defines.h"
#include "Engine/Graphics/graphics_common.h"

#ifdef MC_USE_OPENGL
#include "Engine/Graphics/OpenGL/ogl_defines.h"
#endif


void vertex_buffer_create(VertexBuffer *buffer, f32 *vertices, u32 size);
void vertex_buffer_create_empty(VertexBuffer *buffer, u32 size);
void vertex_buffer_delete(VertexBuffer* buffer); //DOESN'T FREE THE MEMORY
void vertex_buffer_set_data(VertexBuffer *buffer, const void* data, u32 size);
void vertex_buffer_set_layout(VertexBuffer *buffer, BufferLayout layout);

BufferLayout vertex_buffer_get_layout(VertexBuffer *buffer);

void vertex_buffer_bind(VertexBuffer *buffer);
void vertex_buffer_unbind();

void index_buffer_create(IndexBuffer* buffer, u32* indices, u32 count);
void index_buffer_delete(IndexBuffer* buffer); //DOESN'T FREE THE MEMORY
void index_buffer_bind(IndexBuffer* buffer);
void index_buffer_unbind();

#ifdef __cplusplus
}
#endif