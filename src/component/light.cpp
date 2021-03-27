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
    
    default:
        break;
    }
}

DirectionalLight::DirectionalLight():LightBase(ObjectType::DIRECTIONAL_LIGHT)
{
    light_direction = Eigen::Vector3f(0.0f,0.0f,0.0f);
    light_color = Eigen::Vector3f(1.0f,1.0f,1.0f);
}

DirectionalLight::DirectionalLight(const std::string& init_name):LightBase(init_name,ObjectType::DIRECTIONAL_LIGHT)
{
    light_direction = Eigen::Vector3f(0.0f,0.0f,0.0f);
    light_color = Eigen::Vector3f(1.0f,1.0f,1.0f);
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
    light_color = Eigen::Vector3f(1.0f,1.0f,1.0f);
}

PointLight::PointLight(const std::string& init_name):LightBase(init_name,ObjectType::POINT_LIGHT)
{
    light_color = Eigen::Vector3f(1.0f,1.0f,1.0f);
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

