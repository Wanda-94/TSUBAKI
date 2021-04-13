// #version 450 core

// layout(location = 0) out vec4 frag_color;

// #define MAX_DIR_LIGHT_NUM 4
// #define MAX_POINT_LIGHT_NUM 100
// #define CONVERT_SRGB

// struct DirLight{
//     vec3 dir;
//     vec3 color;
// };

// struct PointLight{
//     vec3 location;
//     vec3 color;
//     float attenuation;
// };

// in vec2 vs_uv;
// in vec3 vs_position;
// in mat4 vs_transform_matrix;

// uniform vec3 view_position;

// uniform int dir_light_num;
// uniform int point_light_num;
// uniform DirLight[MAX_DIR_LIGHT_NUM] dir_light_array;
// uniform PointLight[MAX_POINT_LIGHT_NUM] point_light_array;

// uniform bool use_albedo_texture;
// uniform bool use_DEM_normal_texture;
// uniform bool use_metallic_texture;
// uniform bool use_roughness_texture;


// //uniform bool use_ao_texture;

// uniform sampler2D albedo_texture;
// uniform sampler2D DEM_normal_texture;
// uniform sampler2D metallic_texture;
// uniform sampler2D roughness_texture;


// //uniform sampler2D ao_texture;

// uniform vec3 albedo;
// uniform float metallic;
// uniform float roughness;

// //uniform float ao;

// uniform bool use_ambient_texture;
// //3d texture?
// uniform vec3 ambient_color;

// const float PI = 3.1415926;

// vec3 GetNormal(vec2 uv)
// {
//     vec3 res;
//     if(use_DEM_normal_texture == true)
//     {
//         //calculate .......
//         res = texture(DEM_normal_texture,uv).rgb;
//         res = normalize(res);
//         res = inverse(transpose(mat3(vs_transform_matrix)))*res;
//         res = normalize(res);
//     }
//     else
//     {
//         res = vec3(0.0f,0.0f,1.0f);
//     }
//     return res;
// }
// vec3 GetAlbedo(vec2 uv)
// {
//     vec3 res;
//     if(use_albedo_texture == true)
//     {
//         #ifdef CONVERT_SRGB
//             res =  pow(texture(albedo_texture,uv).rgb,vec3(2.2));
//         #else
//             res =  texture(albedo_texture,uv).rgb;
//         #endif
//     }
//     else
//     {
//         res = albedo;
//     }
//     return res;
// }
// float GetMetallic(vec2 uv)
// {
//     float res;
//     if(use_metallic_texture == true)
//     {
//         res = texture(metallic_texture,uv).r;
//     }
//     else
//     {
//         res = metallic;
//     }
//     return res;
// }
// float GetRoughness(vec2 uv)
// {
//     float res;
//     if(use_roughness_texture == true)
//     {
//         res = texture(roughness_texture,uv).r;
//     }
//     else
//     {
//         res = roughness;
//     }
//     return res;
// }

// float DistributionGGX(vec3 N, vec3 H, float roughness)
// {
//     float a = roughness*roughness;
//     float a2 = a*a;
//     float NdotH = max(dot(N, H), 0.0);
//     float NdotH2 = NdotH*NdotH;

//     float nom   = a2;
//     float denom = (NdotH2 * (a2 - 1.0) + 1.0);
//     denom = PI * denom * denom;

//     return nom / denom;
// }
// float GeometrySchlickGGX(float NdotV, float roughness)
// {
//     float r = (roughness + 1.0);
//     float k = (r*r) / 8.0;

//     float nom   = NdotV;
//     float denom = NdotV * (1.0 - k) + k;

//     return nom / denom;
// }
// float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
// {
//     float NdotV = max(dot(N, V), 0.0);
//     float NdotL = max(dot(N, L), 0.0);
//     float ggx2 = GeometrySchlickGGX(NdotV, roughness);
//     float ggx1 = GeometrySchlickGGX(NdotL, roughness);

//     return ggx1 * ggx2;
// }
// vec3 fresnelSchlick(float cosTheta, vec3 F0)
// {
//     return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
// }
// vec3 GetAmbient()
// {
//     vec3 res;
//     if(use_ambient_texture == true)
//     {
//         res = ambient_color;
//     }
//     else
//     {
//         res = ambient_color;
//     }
//     return res;
// }
// void main()
// {
//     vec2 uv = vec2(vs_uv.x,1.0f-vs_uv.y);
//     vec3 albedo_ = GetAlbedo(uv);
//     vec3 normal_ = GetNormal(uv);
//     float metallic_ = GetMetallic(uv);
//     float roughness_ = GetRoughness(uv);

//     vec3 view_vector = normalize(view_position-vs_position);
//     vec3 F0 = vec3(0.04f);
//     F0 = mix(F0,albedo_,metallic_);
//     vec3 res_color = vec3(0.0f);

//     for(int i=0;i<dir_light_num;i++)
//     {
//         vec3 light_vector = normalize(-dir_light_array[i].dir);
//         vec3 half_vector = normalize(view_vector + light_vector);
//         vec3 radiance = dir_light_array[i].color;

//         float NDF = DistributionGGX(normal_,half_vector,roughness_);
//         float G = GeometrySmith(normal_,view_vector,light_vector,roughness_);
//         vec3 F = fresnelSchlick(max(dot(half_vector,view_vector),0.0f),F0);

//         vec3 nominator = NDF*G*F;
//         float denominator = 4.0f*max(dot(normal_,view_vector),0.0f)*max(dot(normal_,light_vector),0.0f) + 0.001;
//         vec3 specular = nominator/denominator;
//         vec3 kS = F;
//         vec3 kD = vec3(1.0f) - kS;

//         kD *= 1.0 - metallic_;

//         float NdotL = max(dot(normal_,light_vector),0.0f);

//         res_color += (kD*albedo_/PI +specular)*radiance*NdotL;
//     }
//     for(int i=0;i<point_light_num;i++)
//     {
//         vec3 light_vector = normalize(point_light_array[i].location - vs_position);
//         vec3 half_vector = normalize(view_vector + light_vector);

//         float distance = length(point_light_array[i].location - vs_position);
//         float attenuation = point_light_array[i].attenuation;
//         attenuation = 10000.0f*attenuation/(distance*distance);

//         vec3 radiance = point_light_array[i].color * attenuation ;

//         float NDF = DistributionGGX(normal_,half_vector,roughness_);
//         float G = GeometrySmith(normal_,view_vector,light_vector,roughness_);
//         vec3 F = fresnelSchlick(max(dot(half_vector,view_vector),0.0f),F0);

//         vec3 nominator = NDF*G*F;
//         float denominator = 4.0f*max(dot(normal_,view_vector),0.0f)*max(dot(normal_,light_vector),0.0f) + 0.001;
//         vec3 specular = nominator/denominator;
//         vec3 kS = F;
//         vec3 kD = vec3(1.0f) - kS;

//         kD *= 1.0 - metallic_;

//         float NdotL = max(dot(normal_,light_vector),0.0f);

//         res_color += (kD*albedo_/PI +specular)*radiance*NdotL;

//     }

//     vec3 ambient = GetAmbient();

//     res_color += ambient*albedo_;

//     res_color = res_color /(res_color+vec3(1.0f));

//     res_color = pow(res_color,vec3(1.0f/2.2f));

//     //frag_color = vec4(vs_view_position,1.0f);
//     frag_color = vec4(res_color,1.0f);
// }


#version 450 core

layout(location = 0) out vec4 frag_color;

in vec2 vs_uv;
in vec3 vs_position;
in mat4 vs_transform_matrix;

uniform sampler2D DEM_normal_texture;

vec3 GetNormal(vec2 uv)
{
    vec3 res;
    res = texture(DEM_normal_texture,uv).rgb;
    res = normalize(res);
    res = res*2.0f - 1.0f;
    res = normalize(res);
    res = inverse(transpose(mat3(vs_transform_matrix)))*res;
    res = normalize(res);
    return res;
}

void main()
{
    vec2 uv = vec2(vs_uv.x,1.0f-vs_uv.y);
    vec3 normal = GetNormal(uv);
    frag_color = vec4(texture(DEM_normal_texture,uv).rgb,1.0f);
}