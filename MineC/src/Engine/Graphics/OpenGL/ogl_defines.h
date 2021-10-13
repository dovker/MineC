#pragma once

#ifdef MC_USE_OPENGL

#ifdef __cplusplus
extern "C" {
#endif

#include "Engine/defines.h"
#include "Engine/Containers/dynamic_array.h"
#include "Engine/Graphics/graphics_common.h"

typedef struct VertexBuffer
{
    u32 id;
    BufferLayout layout;
} VertexBuffer;

typedef struct IndexBuffer
{
    u32 id;
    u32 count;
} IndexBuffer;

typedef struct VertexArray 
{
    u32 id;
    DynamicArray vertex_buffers;
    IndexBuffer *index_buffer;
} VertexArray;

typedef struct Shader 
{
    u32 id;
    const char* path;
} Shader;

typedef struct UniformBuffer
{
    u32 id;
    u32 binding;
} UniformBuffer;

#ifdef __cplusplus
}
#endif

#endif