#ifndef __TSUBAKI_TRANSFORM__
#define __TSUBAKI_TRANSFORM__

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

class Transform{
public:
    Transform();
    Transform(const Transform& t);
    Transform(const Eigen::Vector3f& init_location,const Eigen::Quaternionf& init_rotation,const Eigen::Vector3f& init_scale);
    virtual ~Transform();
    void SetLocation(const Eigen::Vector3f& new_location);
    void SetRotation(const Eigen::Quaternionf& new_rotation);
    void SetScale(const Eigen::Vector3f& new_scale);
    void SetTransformMatrix(const Eigen::Matrix4f& new_transform_matrix);
    Eigen::Vector3f GetLocation() const;
    Eigen::Quaternionf GetRotaion() const;
    Eigen::Vector3f GetScale() const;
    Eigen::Matrix4f GetTransformMatrix() const;
    Transform& operator=(const Transform& t);
private:
    void UpdateTransformMatrix();
    void UpdateStatus();
    Eigen::Vector3f location;
    Eigen::Vector3f scale;
    Eigen::Quaternionf rotation;
    Eigen::Matrix4f transform_matrix;
};

#endif