#shader vertex
#version 450

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

layout(location = 2) uniform mat4 model;
layout(location = 3) uniform mat4 view;
layout(location = 4) uniform mat4 projection;

layout(location = 5) uniform vec3 light_pos = vec3(10.0, 10.0, 10.0);

// Inputs from vertex shader
out VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} vs_out;

void main(void)
{
    // Calculate view-space coordinate
    vec4 P = model * position;

    // Calculate normal in view-space
    mat4 normalMatrix = transpose(inverse(model));
    vs_out.N = mat3(normalMatrix) * normal;

    // Calculate light vector
    vs_out.L = light_pos - P.xyz;

    // Calculate view vector
    vs_out.V = P.xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = projection * view * P;
}

#shader fragment
#version 450

layout(location = 6) uniform vec3 camera_pos;
out vec4 color;

// Input from vertex shader
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} fs_in;

// Material properties
layout(location = 10) uniform vec4 diffuse_albedo = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;

vec3 rim_lighting(vec3 N, vec3 V)
{
    // Calculate the rim factor
    float f = 1.0 - dot(N, V);
    // Constrain it to the range 0 to 1 using a smoothstep function
    f = smoothstep(0.0, 1.0, f);
    // Raise it to the rim exponent
    f = pow(f, 32.0);
    // Finally, multiply it by the rim color
    return f * vec3(diffuse_albedo);
}

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(camera_pos - fs_in.V);
    vec3 R = reflect(-L,N);

    // Compute the diffuse and specular components for each fragment
    vec3 diffuse = max(dot(N, L), 0.0) * vec3(diffuse_albedo);
    vec3 specular = pow(max(dot(V, R), 0.0), specular_power) * specular_albedo;
    vec3 rim = rim_lighting(N,V);

    // Write final color to the framebuffer
    color = vec4(diffuse + specular, 1.0) + diffuse_albedo*0.1;
}