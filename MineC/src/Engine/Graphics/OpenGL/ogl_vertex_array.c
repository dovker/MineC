#ifdef MC_USE_OPENGL

#include "glad/glad.h"
#include "ogl_defines.h"
#include "Engine/Graphics/vertex_array.h"
#include "Engine/Containers/dynamic_array.h"

GLenum data_type_to_GLenum(McDataType dt)
{
    switch(dt)
    {
        case MC_FLOAT:   return GL_FLOAT;
        case MC_FLOAT2:  return GL_FLOAT;
        case MC_FLOAT3:  return GL_FLOAT;
        case MC_FLOAT4:  return GL_FLOAT;
        case MC_MAT3:    return GL_FLOAT;
        case MC_MAT4:    return GL_FLOAT;
        case MC_INT:     return GL_INT;
        case MC_INT2:    return GL_INT;
        case MC_INT3:    return GL_INT;
        case MC_INT4:    return GL_INT;
        case MC_BOOL:    return GL_BOOL;
        default: break;
    }
    MC_ASSERT(false, "Data Type doesn't exist!!");
    return 0;
}

void vertex_array_create(VertexArray *array)
{
    #ifdef MC_OPENGL_4_5
        glCreateVertexArrays(1, &array->id);
    #else
        glGenVertexArrays(1, &array->id);
    #endif
    array->vertex_buffers = dynamic_array_create();
}

void vertex_array_delete(VertexArray *array)
{
    glDeleteVertexArrays(1, &array->id);
    dynamic_array_free(&array->vertex_buffers);
}

void vertex_array_add_index_buffer(VertexArray *array, IndexBuffer *buffer)
{
    glBindVertexArray(array->id);
    index_buffer_bind(buffer);

    array->index_buffer = buffer;
}

void vertex_array_add_vertex_buffer(VertexArray *array, VertexBuffer *buffer)
{
    BufferLayout layout = vertex_buffer_get_layout(buffer);

    MC_ASSERT(layout.count, "Vertex Buffer has no layout!");
    
    glBindVertexArray(array->id);
    vertex_buffer_bind(buffer);
    
    u32 index = 0;
    for (u32 i = 0; i < layout.count; i++)
    {
        BufferElement element = layout.elements[i];
        
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
            data_type_component_count(element.type),
            data_type_to_GLenum(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            layout.stride,
            (const void*)element.offset);

        index++;
    }
    
    dynamic_array_add(&array->vertex_buffers, VertexBuffer*, buffer);
}

IndexBuffer* vertex_array_get_index_buffer(VertexArray *array)
{
    return array->index_buffer;
}

DynamicArray vertex_array_get_vertex_buffers(VertexArray *array)
{
    return array->vertex_buffers;
}

void vertex_array_bind(VertexArray *array)
{
    glBindVertexArray(array->id);
}

void vertex_array_unbind(VertexArray *array)
{
    glBindVertexArray(0);
}

#endif