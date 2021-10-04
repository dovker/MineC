#ifdef MC_USE_OPENGL

#include "glad/glad.h"
#include "ogl_defines.h"

#include "Engine/Graphics/buffer.h"

void vertex_buffer_create(VertexBuffer *buffer, f32 *vertices, u32 size)
{
    #ifdef MC_OPENGL_4_5
        glCreateBuffers(1, &buffer->id);
    #else
        glGenBuffers(1, &buffer->id);
    #endif

    glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void vertex_buffer_create_empty(VertexBuffer *buffer, u32 size)
{
    #ifdef MC_OPENGL_4_5
        glCreateBuffers(1, &buffer->id);
    #else
        glGenBuffers(1, &buffer->id);
    #endif

    glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
    glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
}

void vertex_buffer_delete(VertexBuffer* buffer)
{
    glDeleteBuffers(1, &buffer->id);
}

BufferLayout vertex_buffer_get_layout(VertexBuffer *buffer)
{
    return buffer->layout;
}

void vertex_buffer_set_data(VertexBuffer *buffer, const void* data, u32 size)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void vertex_buffer_set_layout(VertexBuffer *buffer, BufferLayout layout)
{
    buffer->layout = layout;
}

void vertex_buffer_bind(VertexBuffer *buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
}

void vertex_buffer_unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void index_buffer_create(IndexBuffer* buffer, u32* indices, u32 count)
{
    #ifdef MC_OPENGL_4_5
        glCreateBuffers(1, &buffer->id);
    #else
        glGenBuffers(1, &buffer->id);
    #endif

    glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);

    buffer->count = count;
}

void index_buffer_delete(IndexBuffer* buffer)
{
    glDeleteBuffers(1, &buffer->id);
}

void index_buffer_bind(IndexBuffer* buffer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
}

void index_buffer_unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

#endif