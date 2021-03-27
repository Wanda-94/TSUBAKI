#ifndef __TSUBAKI_OBJECT__
#define __TSUBAKI_OBJECT__

#include <string>
#include <component/transform.h>
#include <utility/controller.h>
#include <utility/basic.h>
#include <iostream>

class Object{
public:
    Object();
    Object(const std::string init_name);
    Object(const std::string init_name,const ObjectType& init_object_type);
    Object(const ObjectType& init_object_type);
    virtual ~Object();
    //some function with transform
    virtual void Update(float delta_time);
    unsigned int GetObjectID() const;
    std::string GetObjectName() const;
    ObjectType GetObjectType() const;
    Transform* GetTransform() const;
    Transform GetTransformCopy() const;
    Eigen::Vector3f GetLocation() const;
    Eigen::Quaternionf GetRotation() const;
    Eigen::Vector3f GetScale() const;
    Eigen::Matrix4f GetTransformMatrix() const;
    void SetTransform(const Transform& new_transform);
    void SetTransformMatrix(const Eigen::Matrix4f& new_transform_matrix);
    void SetLocation(const Eigen::Vector3f& new_location);
    void SetRotation(const Eigen::Quaternionf& new_rotation);
    void SetScale(const Eigen::Vector3f& new_scale);
protected:

private:
    unsigned int ID;
    std::string name;
    ObjectType type;
    Transform* transform;
};


#endif