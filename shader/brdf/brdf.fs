#version 450 core
layout(location = 0) out vec4 frag_color;

in vec3 vs_position;
in vec3 vs_normal;
in vec2 vs_uv;

void main()
{
    frag_color = vec4(0.0f,1.0f,1.0f,1.0f);
}