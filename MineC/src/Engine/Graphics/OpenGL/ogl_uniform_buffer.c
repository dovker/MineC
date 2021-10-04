#ifdef MC_USE_OPENGL
#include <stdio.h>
#include <string.h>

#include "glad/glad.h"
#include "ogl_defines.h"
#include "Engine/Graphics/uniform_buffer.h"

void uniform_buffer_create(UniformBuffer *buffer, u32 size, u32 binding)
{
    #ifdef MC_OPENGL_4_5
    glCreateBuffers(1, &buffer->id);

    glNamedBufferData(buffer->id, size, NULL, GL_DYNAMIC_DRAW);
    #else
    glGenBuffers(1, &buffer->id);
  
    glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
    glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    #endif

    glBindBufferBase(GL_UNIFORM_BUFFER, binding, buffer->id);
    buffer->binding = binding;
}

void uniform_buffer_delete(UniformBuffer *buffer)
{   
    glDeleteBuffers(1, &buffer->id);
}

void uniform_buffer_set_data(UniformBuffer *buffer, void* data, u32 size, u32 offset)
{
    #ifdef MC_OPENGL_4_5
    glNamedBufferSubData(buffer->id, offset, size, data);
    #else
    glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    #endif
}

#endif