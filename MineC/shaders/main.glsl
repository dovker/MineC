#shader vertex

#version 330 core
layout (location = 0) in vec3 aPos;

layout(std140) uniform Camera
{
    mat4 u_Projection;
    mat4 u_View;
};

void main()
{
    gl_Position = u_Projection * u_View * vec4(aPos, 1.0);
}

#shader fragment

#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0, 0.5, 0.2, 1.0);
}