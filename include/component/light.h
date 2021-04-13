#ifndef __TSUBAKI_LIGHT__
#define __TSUBAKI_LIGHT__

#include <Eigen/Core>
#include <utility/basic.h>
#include <component/object.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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

    //virtual void Update(float delta_time) override;
    virtual void DrawGUI() override;

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

    virtual void DrawGUI() override;

    Eigen::Vector3f GetLightColor() const;
    float GetAttenuation() const;
    void SetLightColor(const Eigen::Vector3f& new_light_color);
    void SetAttenuation(float new_attenuation);
private:
    Eigen::Vector3f light_color;
    float attenuation;
};

class AmbientLight : public LightBase{
public:
    AmbientLight();
    AmbientLight(const std::string& init_name);
    ~AmbientLight();

    virtual void DrawGUI() override;

    Eigen::Vector3f GetLightColor() const;
    void SetLightColor(const Eigen::Vector3f& new_light_color);
private:
    Eigen::Vector3f light_color;
};

#endif