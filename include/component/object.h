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

    void AttachToParent(Object* new_parent);
    void DetachFromParent();
    Object* GetParent();
    void AddChild(Object* new_child);
    void RemoveChild(Object* rm_child);
    int GetChildNum();
    Object* GetChild(int index);

protected:

private:
    void UpdateLocalMatrix();
    void UpdateChilds();
    void UpdateChilds(const Eigen::Matrix4f& parent_curr_transform_matrix);


    unsigned int ID;
    std::string name;
    ObjectType type;
    Transform* transform;
    Eigen::Matrix4f local_matrix;
    Object* parent;
    std::vector<Object*> childs;
};


#endif