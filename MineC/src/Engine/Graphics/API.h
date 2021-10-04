#pragma once

#include "Engine/Graphics/vertex_array.h"
#include "Engine/Graphics/graphics_common.h"

void graphics_init();
void graphics_set_viewport(u32 x, u32 y, u32 width, u32 height);
void graphics_set_clear_color(f32 r, f32 g, f32 b, f32 a);
void graphics_set_blending_mode(McBlendingMode blending);

void graphics_toggle_depth_test(b8 toggle);
void graphics_toggle_backface_culling(b8 toggle);
void graphics_toggle_blending(b8 toggle);

void graphics_clear();

void graphics_draw_indexed(VertexArray* array);
void graphics_draw_indexed_count(VertexArray* array, u32 index_count);