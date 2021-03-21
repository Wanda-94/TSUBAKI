#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 transform_matrix;
uniform mat4 camera_matrix;
uniform mat4 projection_matrix;

out vec3 vs_position;
out vec3 vs_normal;
out vec2 vs_uv;

void main()
{
    gl_Position = projection_matrix*camera_matrix*transform_matrix*vec4(position,1.0f);
    //gl_Position = vec4(position,1.0f);
    vs_position = vec3((transform_matrix*vec4(position,1.0f)).xyz);
    vs_normal = inverse(transpose(mat3(transform_matrix)))*normal;
    vs_normal = normalize(vs_normal);
    vs_uv = uv;
}