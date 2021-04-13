#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 transform_matrix;
uniform mat4 camera_matrix;
uniform mat4 projection_matrix;

uniform float z_scale;
uniform sampler2D DEM_texture;

out vec2 vs_uv;
out vec3 vs_position;
out mat4 vs_transform_matrix;


float GetHeight(vec2 uv_)
{
    float height = texture(DEM_texture,uv_).r;
    height = height * z_scale;
    //height = height * 100000.0f;
    return height;
}

void main()
{   
    vec2 uv_ = vec2(uv.x,1.0f - uv.y);
    vec3 positoin_ = vec3(position.xy,GetHeight(uv_));
    gl_Position = projection_matrix*camera_matrix*transform_matrix*vec4(positoin_,1.0f);
    vs_position = vec3((transform_matrix*vec4(positoin_,1.0f)).xyz);
    vs_transform_matrix = transform_matrix;
    vs_uv = uv;
}