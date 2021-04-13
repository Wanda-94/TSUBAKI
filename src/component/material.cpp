#include <component/material.h>

MaterialBase::MaterialBase(const std::string& init_label,const MaterialType& init_material_type)
{
    this->label = init_label;
    this->material_type = init_material_type;
}

MaterialBase::~MaterialBase()
{

}

std::string MaterialBase::GetLabel()
{
    return this->label;
}

MaterialType MaterialBase::GetMaterialType()
{
    return this->material_type;
}

Material::Material(const std::string& init_label,
Shader* init_shader):MaterialBase(init_label,MaterialType::MATERIAL_BRDF)
{
    shader = init_shader;
    albedo = Eigen::Vector3f(1.0f,1.0f,1.0f);
    metallic = 0.0f;
    roughness = 1.0f;
    for(int i=0;i<texture_type_num;i++)
    {
        texture_map[(TextureType)(i)] = nullptr;
    }
}

Material::~Material()
{

}

void Material::AddTexture(TextureType add_texture_type,
Texture* add_texture)
{
    texture_map[add_texture_type] = add_texture;
}

void Material::RemoveTexture(TextureType rm_texture_type)
{
    texture_map[rm_texture_type] = nullptr;
}

void Material::UseMaterial(Object* object)
{
    Eigen::Matrix4f& transform_matrix = object->GetTransformMatrix();
    shader->UseShader();
    SetTextureStatus();
    SetCameraStatus();
    SetModelStatus(transform_matrix);
    SetLightStatus();
}

void Material::SetTextureStatus()
{
    for(auto t = texture_map.begin();t!=texture_map.end();t++)
    {
        if(t->second != nullptr)
        {
            shader->SetUniformBool(ShaderUseTextureLabel[(int)t->first],true);
            t->second->ActiveTexture((int)(t->first)+1);
            shader->SetUniformInt(ShaderTextureLabel[(int)(t->first)],(int)(t->first)+1);
        }
        else
        {
            shader->SetUniformBool(ShaderUseTextureLabel[(int)t->first],false);
            switch (t->first)
            {
            case TextureType::TEXTURE_ALBEDO:
                shader->SetUniformVec3("albedo",this->albedo);
                /* code */
                break;
            case TextureType::TEXTURE_METALLIC:
                shader->SetUniformFloat("metallic",this->metallic);
                break;
            case TextureType::TEXTURE_ROUGHNESS:
                shader->SetUniformFloat("roughness",this->roughness);
                break;
            default:
                break;
            }
        }
    }
}

void Material::SetCameraStatus()
{
    Camera* curr_camera = Controller::GetCurrCamera();
	shader->SetUniformVec3("view_position",curr_camera->GetLocation());
	shader->SetUniformMatrix4x4("camera_matrix",curr_camera->GetToLocalMatrix());
	shader->SetUniformMatrix4x4("projection_matrix",  curr_camera->GetProjectionMatrix());
}

void Material::SetModelStatus(const Eigen::Matrix4f& transform_matrix)
{
    shader->SetUniformMatrix4x4("transform_matrix",transform_matrix);
}

void Material::SetLightStatus()
{
	shader->SetUniformInt("dir_light_num",Controller::GetDirectionalLightNum());
	for(int i=0;i<Controller::GetDirectionalLightNum();i++)
	{
		DirectionalLight* dir_light = Controller::GetDirectionalLight(i);
		shader->SetUniformVec3("dir_light_array["+std::to_string(i)+"].dir",dir_light->GetLightDirection());
		shader->SetUniformVec3("dir_light_array["+std::to_string(i)+"].color",dir_light->GetLightColor());
	}
    shader->SetUniformInt("point_light_num",Controller::GetPointLightNum());
    for(int i=0;i<Controller::GetPointLightNum();i++)
    {
        PointLight* point_light = Controller::GetPointLight(i);
        shader->SetUniformVec3("point_light_array["+std::to_string(i)+"].location",point_light->GetLocation());
		shader->SetUniformVec3("point_light_array["+std::to_string(i)+"].color",point_light->GetLightColor());
        shader->SetUniformFloat("point_light_array["+std::to_string(i)+"].attenuation",point_light->GetAttenuation());
    }
    if(Controller::GetAmbientLightNum()!=0)
    {
        AmbientLight* ambient_light = Controller::GetAmbientLight(0);
        shader->SetUniformBool("use_ambient_texture",false);
        shader->SetUniformVec3("ambient_color",ambient_light->GetLightColor());
    }
    else
    {
        shader->SetUniformBool("use_ambient_texture",false);
        shader->SetUniformVec3("ambient_color",Eigen::Vector3f(0.0f,0.0f,0.0f));
    }
}

TerrainMaterial::TerrainMaterial(const std::string& init_label,
Shader* init_shader):MaterialBase(init_label,MaterialType::MATERIAL_TERRAIN)
{
    this->shader = init_shader;
    this->DEM_texture = nullptr;
    this->DEM_normal_texture = nullptr;
    this->z_scale = 1.0f;
}

TerrainMaterial::~TerrainMaterial()
{

}

void TerrainMaterial::UseMaterial(Object* object)
{
    shader->UseShader();
    DEM_texture->ActiveTexture(1);
    DEM_normal_texture->ActiveTexture(2);
    shader->SetUniformInt("DEM_texture",1);
    shader->SetUniformInt("DEM_normal_texture",2);
    shader->SetUniformFloat("z_scale",this->z_scale);
    shader->SetUniformMatrix4x4("camera_matrix",Controller::GetCurrCamera()->GetToLocalMatrix());
    shader->SetUniformMatrix4x4("projection_matrix",Controller::GetCurrCamera()->GetProjectionMatrix());
    shader->SetUniformMatrix4x4("transform_matrix",object->GetTransformMatrix());

}

void TerrainMaterial::SetZScale(float new_z_scale)
{
    this->z_scale = new_z_scale;
}

void TerrainMaterial::SetDEMData(Texture* new_DEM_texture,
Texture* new_DEM_normal_texture)
{
    this->DEM_texture = new_DEM_texture;
    this->DEM_normal_texture = new_DEM_normal_texture;
}