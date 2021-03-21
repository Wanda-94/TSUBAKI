#ifndef __TSUBAKI_OBJECT__
#define __TSUBAKI_OBJECT__

#include <string>
#include <component/transform.h>
#include <utility/controller.h>
#include <iostream>

class Object{
public:
    Object();
    Object(const std::string init_name);
    virtual ~Object();
    //some function with transform
    virtual void Update(float delta_time);
    Transform* GetTransform();
    Transform GetTransformCopy();
    void SetTransform(const Transform& new_transform);
    void SetLocation(const Eigen::Vector3f& new_location);
    void SetRotation(const Eigen::Quaternionf& new_rotation);
    void SetScale(const Eigen::Vector3f& new_scale);
private:
    unsigned int ID;
    std::string name;
    Transform* transform;
};


#endif