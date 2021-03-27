#ifndef __TSUBAKI_LIGHT__
#define __TSUBAKI_LIGHT__

#include <Eigen/Core>
#include <utility/basic.h>
#include <component/object.h>


class LightBase : public Object{
public:
    LightBase(const ObjectType& init_light_type);
    LightBase(const std::string& init_name,const ObjectType& init_light_type);
    virtual ~LightBase();
private:

};

class DirectionalLight : public LightBase{
public:
    DirectionalLight();
    DirectionalLight(const std::string& init_name);
    ~DirectionalLight();
    Eigen::Vector3f GetLightDirection() const;
    Eigen::Vector3f GetLightColor() const;
    void SetLightDirection(const Eigen::Vector3f& new_light_direction);
    void SetLightColor(const Eigen::Vector3f& new_light_color);
private:
    Eigen::Vector3f light_direction;
    Eigen::Vector3f light_color;
};

class PointLight : public LightBase{
public:
    PointLight();
    PointLight(const std::string& init_name);
    ~PointLight();
    Eigen::Vector3f GetLightColor() const;
    void SetLightColor(const Eigen::Vector3f& new_light_color);
private:
    Eigen::Vector3f light_color;
};


#endif