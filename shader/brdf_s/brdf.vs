#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in ivec4 bone_index;
layout(location = 4) in vec4 bone_weight;

uniform mat4 transform_matrix;
uniform mat4 camera_matrix;
uniform mat4 projection_matrix;

uniform float frame_index;
uniform int frame_num;
uniform int bone_num;
uniform int texture_width;
uniform int texture_height;
uniform sampler2D animation_texture;

mat4 GetTransformMatrix(float frame_index,int bi)
{
    //int frame_index_a = (int)(frame_index);
    //int frame_index_b = frame_index_a + 1;
    mat4 trans_matrix;
    trans_matrix[0][0] = 1.0f;
    trans_matrix[1][1] = 1.0f;
    trans_matrix[2][2] = 1.0f;
    trans_matrix[3][3] = 1.0f;
    return trans_matrix;
}

out vec3 vs_position;
out vec3 vs_normal;
out vec2 vs_uv;

void main()
{
    vec4 final_position = vec4(0.0f);

    for(int i=0;i<4;i++)
    {
        mat4 trans_matrix = GetTransformMatrix(frame_index,bone_index[i]);
        float b_w = bone_weight[i];
        final_position += (trans_matrix * vec4(position,1.0f))*b_w;
    }

    gl_Position = projection_matrix*camera_matrix*transform_matrix*final_position;
    vs_position = vec3((transform_matrix*final_position).xyz);
    vs_normal = inverse(transpose(mat3(transform_matrix)))*normal;
    vs_normal = normalize(vs_normal);
    vs_uv = uv;
}