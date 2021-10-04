#ifdef MC_USE_OPENGL
#include <stdio.h>
#include <string.h>

#include "glad/glad.h"
#include "ogl_defines.h"
#include "Engine/Graphics/shader.h"

#define SHADER_FILE_READ_CHUNK 256

u32 ogl_compile_shader(GLenum shaderType, const char* source)
{
    u32 id = glCreateShader(shaderType);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    int result;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        const char* shdType;
        switch(shaderType)
        {
            case GL_VERTEX_SHADER: shdType = "vertex  "; break;
            case GL_FRAGMENT_SHADER: shdType = "fragment"; break;
            case GL_GEOMETRY_SHADER: shdType = "geometry"; break;
        }
        printf("Failed to compile %s Shader\n", shdType);
        printf(message);
        glDeleteShader(id);

        free(message);
        return 0;
    }

    return id;
}

void shader_create(Shader* shader, const char* filepath)
{
    shader->path = filepath;
    shader->id = _shader_compile(filepath);
}

void shader_recompile(Shader* shader)
{
    MC_ASSERT(shader->path, "Shader not initialized yet!")
    shader->id = _shader_compile(shader->path);
}

void shader_set_uniform_buffer_binding(Shader *shader, UniformBuffer *buffer, const char *name)
{
    u32 buffer_index = glGetUniformBlockIndex(shader->id, name);   
    glUniformBlockBinding(shader->id, buffer_index, buffer->binding);
}

void shader_delete(Shader* shader)
{
    glDeleteProgram(shader->id);
}

void shader_bind(Shader* shader)
{
    glUseProgram(shader->id);
}

void shader_unbind()
{
    glUseProgram(0);
}

char* _concat_strings(const char* s1, const char* s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    const char* concatenatedString = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
    MC_ASSERT(concatenatedString, "FAILED TO ALLOCTE MEMORY WHEN CONCATENATING STRINGS");

    strcpy(concatenatedString, s1);
    strcat(concatenatedString, s2, len2);

    return concatenatedString;
}

char* _file_get_line(FILE *file)
{
    char* line = NULL;
    char chunk[SHADER_FILE_READ_CHUNK];
    if(fgets(chunk, sizeof(chunk), file))
    {
        line = (char*)malloc(sizeof(chunk));
        strcpy(line, chunk);
        
        while(!strchr(chunk, '\n'))
        {
            if (fgets(chunk, sizeof(chunk), file))
            {
                line = _concat_strings(line, chunk);
            }
            else
            {
                break;
            }
        }
    }
    return line;
}

u32 _shader_compile(const char *filepath)
{
    enum ShaderType { ST_VERTEX = 0, ST_FRAGMENT, ST_GEOMETRY };
    const char* sources[3] = { '\0', '\0', '\0' };
    
    {
        FILE* shaderFile = fopen(filepath, "r");
        MC_ASSERT(shaderFile, "FILE OPEN ERROR: FILE DOESN'T EXIST!");

        const char* line = _file_get_line(shaderFile);
        u32 currentShader;
        while(line)
        {
            if(strstr(line, "#shader"))
            {
                if(strstr(line, "vertex"))
                {
                    currentShader = ST_VERTEX;
                }
                else if(strstr(line, "fragment"))
                {
                    currentShader = ST_FRAGMENT;
                }
                else if (strstr(line, "geometry"))
                {
                    currentShader = ST_GEOMETRY;
                }
                else
                {
                    MC_ASSERT(false, "FAILED PARSING SHADER, SHADER TYPE NOT FOUNT")
                }
            }
            else
            {
                if (sources[currentShader]) //If defined already
                {
                    sources[currentShader] = _concat_strings(sources[currentShader], line);
                }
                else
                {
                    sources[currentShader] = malloc(sizeof(line) + 1);
                    strcpy(sources[currentShader], line);
                }
            }

            line = _file_get_line(shaderFile);
        }
        free(line);
        fclose(shaderFile);
    }

    u32 id = glCreateProgram();

    u32 vs = 0, fs = 0, gs = 0;
    if(sources[ST_VERTEX])
    {
        vs = ogl_compile_shader(GL_VERTEX_SHADER, sources[ST_VERTEX]);
        glAttachShader(id, vs);
    }
    if(sources[ST_FRAGMENT])
    {
        fs = ogl_compile_shader(GL_FRAGMENT_SHADER, sources[ST_FRAGMENT]);
        glAttachShader(id, fs);
    }
    if(sources[ST_GEOMETRY])
    {
        gs = ogl_compile_shader(GL_GEOMETRY_SHADER, sources[ST_GEOMETRY]);
        glAttachShader(id, gs);
    }

    glLinkProgram(id);

    if (vs)
    {
        glDeleteShader(vs);
        free(sources[ST_VERTEX]);
    }
    if (fs)
    {
        glDeleteShader(fs);
        free(sources[ST_FRAGMENT]);
    }
    if (gs)
    {
        glDeleteShader(gs);
        free(sources[ST_GEOMETRY]);
    }

    return id;
}

#endif