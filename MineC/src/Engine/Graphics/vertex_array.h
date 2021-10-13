#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Engine/defines.h"
#include "Engine/Graphics/buffer.h"
#include "Engine/Containers/dynamic_array.h"

#ifdef MC_USE_OPENGL
#include "Engine/Graphics/OpenGL/ogl_defines.h"
#endif

typedef struct VertexArray VertexArray;

void vertex_array_create(VertexArray *array);
void vertex_array_delete(VertexArray *array);

void vertex_array_add_index_buffer(VertexArray *array, IndexBuffer *buffer);
void vertex_array_add_vertex_buffer(VertexArray *array, VertexBuffer *buffer);

IndexBuffer* vertex_array_get_index_buffer(VertexArray *array);
DynamicArray vertex_array_get_vertex_buffers(VertexArray *array);

void vertex_array_bind(VertexArray *array);
void vertex_array_unbind(VertexArray *array);

#ifdef __cplusplus
}
#endif