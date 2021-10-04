#include "Engine/Graphics/graphics_common.h"

#include "stdarg.h"

u32 data_type_size(McDataType dt)
{
    switch(dt)
    {
        case MC_FLOAT:   return 4;
        case MC_FLOAT2:  return 4 * 2;
        case MC_FLOAT3:  return 4 * 3;
        case MC_FLOAT4:  return 4 * 4;
        case MC_MAT3:    return 4 * 3 * 3;
        case MC_MAT4:    return 4 * 4 * 4;
        case MC_INT:     return 4;
        case MC_INT2:    return 4 * 2;
        case MC_INT3:    return 4 * 3;
        case MC_INT4:    return 4 * 4;
        case MC_BOOL:    return 1;
        default: break;
    }
    MC_ASSERT(false, "Data Type doesn't exist!!");
    return 0;
}

u32 data_type_component_count(McDataType dt)
{
    switch(dt)
    {
        case MC_FLOAT:   return 1;
        case MC_FLOAT2:  return 2;
        case MC_FLOAT3:  return 3;
        case MC_FLOAT4:  return 4;
        case MC_MAT3:    return 3 * 3; // 3* float3
        case MC_MAT4:    return 4 * 4; // 4* float4
        case MC_INT:     return 1;
        case MC_INT2:    return 2;
        case MC_INT3:    return 3;
        case MC_INT4:    return 4;
        case MC_BOOL:    return 1;
        default: break;
    }
    MC_ASSERT(false, "Data Type doesn't exist!!");
    return 0;
}

BufferLayout buffer_layout_create(u32 count, ...)
{
    MC_ASSERT(count > MC_MAX_BUFFERELEMENT_COUNT, "Too many arguments passed to a Buffer Layout");
    
    BufferLayout layout;
    layout.stride = 0;
    layout.count = count;
    u32 offset = 0;
    va_list arguments;

    va_start(arguments, count);
    for (u32 i = 0; i < count; i++)        
    {
        McDataType dt = va_arg(arguments, McDataType); 

        BufferElement elem = {dt, data_type_size(dt), offset, false, NULL};

        layout.elements[i] = elem;

        offset += elem.size;
        layout.stride += elem.size;
    }
    va_end(arguments); 

    return layout;
}