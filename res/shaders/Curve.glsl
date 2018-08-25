#shader vertex
#version 450

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

layout(location = 2) uniform mat4 model;
layout(location = 3) uniform mat4 view;
layout(location = 4) uniform mat4 projection;

void main(void)
{
    vec3 p = 4.2*position.xyz;
    gl_Position = projection * view * model * vec4(p, 1.0);
}

#shader fragment
#version 450

layout(location = 11) uniform vec4 uColor = vec4(1.0, 1.0, 1.0, 1.0);
out vec4 color;

void main(void)
{
    color = uColor;
}