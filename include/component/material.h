#ifndef __TSUBAKI_MATERIAL__
#define __TSUBAKI_MATERIAL__

#include <vector>
#include <unordered_map>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <component/shader.h>
#include <component/texture.h>
#include <component/camera.h>
#include <component/light.h>

const int texture_type_num = 4;

enum class TextureType{
    TEXTURE_ALBEDO  = 0 ,
    TEXTURE_NORMAL = 1 ,
    TEXTURE_METALLIC = 2 ,
    TEXTURE_ROUGHNESS = 3
};
const std::string ShaderUseTextureLabel[4] = {
    "use_albedo_texture",
    "use_normal_texture",
    "use_metallic_texture",
    "use_roughness_texture"
};
const std::string ShaderTextureLabel[4] = {
    "albedo_texture",
    "normal_texture",
    "metallic_texture",
    "roughness_texture"
};

class Material{
public:
    Material(const std::string& init_label,Shader* init_shader);
    ~Material();
    void AddTexture(TextureType add_texture_type,
    Texture* add_texture);
    void RemoveTexture(TextureType rm_texture_type);
    void UseMaterial(const Eigen::Matrix4f& transform_matrix);
private:
    void SetTextureStatus();
    void SetCameraStatus();
    void SetModelStatus(const Eigen::Matrix4f& transform_matrix);
    void SetLightStatus();
    std::string label;
    Shader* shader;

    Eigen::Vector3f albedo;
    float metallic;
    float roughness;

    std::unordered_map<TextureType,Texture*> texture_map;
};


#endif