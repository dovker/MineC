#pragma once

#include "Engine/defines.h"

#define MC_MAX_BUFFERELEMENT_COUNT 8

typedef enum
{
    MC_NONE = 0, MC_FLOAT, MC_FLOAT2, MC_FLOAT3, MC_FLOAT4, 
    MC_MAT3, MC_MAT4, 
    MC_INT, MC_INT2, MC_INT3, MC_INT4, 
    MC_BOOL
} McDataType;

u32 data_type_size(McDataType dt);
u32 data_type_component_count(McDataType dt);

typedef struct BufferElement
{
    McDataType type;
    u32 size;
    u32 offset;
    b8 normalized;
    const char* name;
    //TODO: Add support for Normalized OpenGL thing
} BufferElement;

typedef struct BufferLayout
{
    BufferElement elements[MC_MAX_BUFFERELEMENT_COUNT];
    u32 count;
    u32 stride;
} BufferLayout;


BufferLayout buffer_layout_create(u32 count, ...);

typedef enum McBlendingMode
{
    MC_BLENDING_NONE = 0,
    MC_BLENDING_ADDITIVE,
    MC_BLENDING_SUBTRACTIVE,
    MC_BLENDING_REGULAR
} McBlendingMode;

typedef enum McShaderType
{
    MC_SHADER_NONE = 0,
    MC_SHADER_FRAGMENT,
    MC_SHADER_VERTEX,
    MC_SHADER_GEOMETRY,
    MC_SHADER_COMPUTE
} McShaderType;