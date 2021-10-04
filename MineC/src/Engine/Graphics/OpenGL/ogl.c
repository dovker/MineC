#ifdef MC_USE_OPENGL

#include "Engine/Graphics/API.h"
#include "ogl_defines.h"
#include "glad/glad.h"

void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         MC_LOG(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       MC_LOG(message); return;
			case GL_DEBUG_SEVERITY_LOW:          MC_LOG(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: MC_LOG(message); return;
		}
		
		MC_ASSERT(false, "Unknown severity level!");
	}

void graphics_init()
{
    #if defined(MC_DEBUG) && defined(MC_OPENGL_4_5)
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, NULL);
    
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
    #endif

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void graphics_set_viewport(u32 x, u32 y, u32 width, u32 height)
{
    glViewport(x, y, width, height);
}

void graphics_set_clear_color(f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
}

void graphics_set_blending_mode(McBlendingMode blending)
{
    switch(blending)
    {
        case MC_BLENDING_ADDITIVE:
        glBlendFunc(GL_ONE, GL_ONE);
        break;
        case MC_BLENDING_SUBTRACTIVE:
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        break;
        case MC_BLENDING_REGULAR:
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        break;
    }
    MC_ASSERT(false, "BLENDING MODE NOT SUPPORTED");
}

void graphics_toggle_depth_test(b8 toggle)
{
    toggle ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void graphics_toggle_backface_culling(b8 toggle)
{
    toggle ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

void graphics_toggle_blending(b8 toggle)
{
    toggle ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
}

void graphics_clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void graphics_draw_indexed(VertexArray* array)
{
    u32 count = vertex_array_get_index_buffer(array)->count;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void graphics_draw_indexed_count(VertexArray* array, u32 index_count)
{
    u32 count = index_count ? index_count : vertex_array_get_index_buffer(array)->count;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
}
#endif