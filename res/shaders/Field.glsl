#shader vertex
#version 450

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

layout(location = 2) uniform mat4 model;
layout(location = 3) uniform mat4 view;
layout(location = 4) uniform mat4 projection;

layout(location = 5) uniform int n;

uniform samplerBuffer angle;

vec4 rotate(vec4 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return vec4(m * v.xy, v.z, v.w);
}

vec4 calcPosition(int id)
{
    float x = 2.0*float(mod(id,n))/float(n-1) - 1.0;
    float y = 2.0*float(floor(id/n))/float(n-1) - 1.0;
    return vec4(4.2*x, 4.2*y, 0.0, 0.0);
}

void main(void)
{
    vec4 a = texelFetch(angle, gl_InstanceID);
    vec4 offset = calcPosition(gl_InstanceID);
    gl_Position = projection * view * (model * rotate(position, a.x) + offset);
}

#shader fragment
#version 450

layout(location = 10) uniform vec3 camera_pos;
layout(location = 11) uniform vec4 uColor = vec4(1.0, 1.0, 1.0, 1.0);
out vec4 color;

void main(void)
{
    color = uColor;
}