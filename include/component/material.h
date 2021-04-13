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

enum class MaterialType{
    MATERIAL_BASE = 0,
    MATERIAL_BRDF,
    MATERIAL_TERRAIN
};

const int texture_type_num = 4;

enum class TextureType{
    TEXTURE_ALBEDO  = 0 ,
    TEXTURE_NORMAL = 1 ,
    TEXTURE_METALLIC = 2 ,
    TEXTURE_ROUGHNESS = 3 ,
    // TEXTURE_DEM = 4,
    // TEXTURE_DEM_NORMAL = 5
};
const std::string ShaderUseTextureLabel[4] = {
    "use_albedo_texture",
    "use_normal_texture",
    "use_metallic_texture",
    "use_roughness_texture",
    // "use_DEM_texture",
    // "use_DEM_normal_texture"
};
const std::string ShaderTextureLabel[4] = {
    "albedo_texture",
    "normal_texture",
    "metallic_texture",
    "roughness_texture",
    // "DEM_texture",
    // "DEM_normal_texture"
};

class MaterialBase{
public:
    MaterialBase(const std::string& init_label,const MaterialType& init_material_type);
    virtual ~MaterialBase();
    virtual void UseMaterial(Object* object) = 0;
    std::string GetLabel();
    MaterialType GetMaterialType();
private:
    std::string label;
    MaterialType material_type;
};

class Material : public MaterialBase{
public:
    Material(const std::string& init_label,Shader* init_shader);
    ~Material();
    void AddTexture(TextureType add_texture_type,
    Texture* add_texture);
    void RemoveTexture(TextureType rm_texture_type);
    virtual void UseMaterial(Object* object) override;
private:
    void SetTextureStatus();
    void SetCameraStatus();
    void SetModelStatus(const Eigen::Matrix4f& transform_matrix);
    void SetLightStatus();
    
    Shader* shader;

    Eigen::Vector3f albedo;
    float metallic;
    float roughness;

    std::unordered_map<TextureType,Texture*> texture_map;
};

class TerrainMaterial : public MaterialBase{
public:
    TerrainMaterial(const std::string& init_label,Shader* init_shader);
    ~TerrainMaterial();
    virtual void UseMaterial(Object* object) override;
    void SetZScale(float new_z_scale);
    void SetDEMData(Texture* new_DEM_texture,Texture* new_DEM_normal_texture);
private:
    Texture* DEM_texture;
    Texture* DEM_normal_texture;
    Shader* shader;
    float z_scale;
};

#endif