#include <component/light.h>

LightBase::LightBase(const ObjectType& init_light_type):Object(init_light_type)
{
    switch (init_light_type)
    {
    case ObjectType::DIRECTIONAL_LIGHT:
        /* code */
        Controller::InsertDirectionalLight(GetObjectID());
        break;

    case ObjectType::POINT_LIGHT:
        /* code */
        Controller::InsertPointLight(GetObjectID());
        break;
    case ObjectType::AMBIENT_LIGHT:
        Controller::InsertAmbientLight(GetObjectID());
        break;
    default:
        break;
    }
}

LightBase::LightBase(const std::string& init_name,const ObjectType& init_light_type):Object(init_name,init_light_type)
{
    switch (init_light_type)
    {
    case ObjectType::DIRECTIONAL_LIGHT:
        /* code */
        Controller::InsertDirectionalLight(GetObjectID());
        break;

    case ObjectType::POINT_LIGHT:
        /* code */
        Controller::InsertPointLight(GetObjectID());
        break;
    case ObjectType::AMBIENT_LIGHT:
        Controller::InsertAmbientLight(GetObjectID());
        break;
    default:
        break;
    }
}

LightBase::~LightBase()
{
    ObjectType light_type = GetObjectType();
    switch (light_type)
    {
    case ObjectType::DIRECTIONAL_LIGHT:
        /* code */
        Controller::RemoveDirectionalLight(GetObjectID());
        break;

    case ObjectType::POINT_LIGHT:
        /* code */
        Controller::RemovePointLight(GetObjectID());
        break;
    case ObjectType::AMBIENT_LIGHT:
        Controller::RemoveAmbientLight(GetObjectID());
        break;
    default:
        break;
    }
}

DirectionalLight::DirectionalLight():LightBase(ObjectType::DIRECTIONAL_LIGHT)
{
    this->light_direction = Eigen::Vector3f(0.0f,0.0f,0.0f);
    this->light_color = Eigen::Vector3f(1.0f,1.0f,1.0f);
}

DirectionalLight::DirectionalLight(const std::string& init_name):LightBase(init_name,ObjectType::DIRECTIONAL_LIGHT)
{
    this->light_direction = Eigen::Vector3f(0.0f,0.0f,0.0f);
    this->light_color = Eigen::Vector3f(1.0f,1.0f,1.0f);
}

DirectionalLight::~DirectionalLight()
{

}

Eigen::Vector3f DirectionalLight::GetLightDirection() const
{
    return this->light_direction;
}

Eigen::Vector3f DirectionalLight::GetLightColor() const
{
    return this->light_color;
}

void DirectionalLight::SetLightDirection(const Eigen::Vector3f& new_light_direction)
{
    this->light_direction = new_light_direction;
}

void DirectionalLight::SetLightColor(const Eigen::Vector3f& new_light_color)
{
    this->light_color = new_light_color;
}

PointLight::PointLight():LightBase(ObjectType::POINT_LIGHT)
{
    this->light_color = Eigen::Vector3f(1.0f,1.0f,1.0f);
    this->attenuation = 1.0f;
}

PointLight::PointLight(const std::string& init_name):LightBase(init_name,ObjectType::POINT_LIGHT)
{
    this->light_color = Eigen::Vector3f(1.0f,1.0f,1.0f);
    this->attenuation = 1.0f;
}

PointLight::~PointLight()
{

}

Eigen::Vector3f PointLight::GetLightColor() const
{
    return this->light_color;
}

void PointLight::SetLightColor(const Eigen::Vector3f& new_light_color)
{
    this->light_color = new_light_color;
}

float PointLight::GetAttenuation() const
{
    return this->attenuation;
}

void PointLight::SetAttenuation(float new_attenuation)
{
    this->attenuation = new_attenuation;
}

AmbientLight::AmbientLight():LightBase(ObjectType::AMBIENT_LIGHT)
{
    this->light_color = Eigen::Vector3f(0.01f,0.01f,0.01f);
}
AmbientLight::AmbientLight(const std::string& init_name):LightBase(init_name,ObjectType::AMBIENT_LIGHT)
{
    this->light_color = Eigen::Vector3f(0.01f,0.01f,0.01f);
}
AmbientLight::~AmbientLight()
{

}
Eigen::Vector3f AmbientLight::GetLightColor() const
{
    return this->light_color;
}
void AmbientLight::SetLightColor(const Eigen::Vector3f& new_light_color)
{
    this->light_color = new_light_color;
}
