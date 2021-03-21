#ifndef __TSUBAKI_CAMERA__
#define __TSUBAKI_CAMERA__

#include<Eigen/Core>
#include<Eigen/Geometry>

class Camera{
public:
    Camera();
    ~Camera();
    void SetLocation(const Eigen::Vector3f& new_location);
    void SetRotation(const Eigen::Quaternionf& new_rotation);
    Eigen::Matrix4f GetToLocalMatrix();
    Eigen::Matrix4f GetProjectionMatrix();
private:
    void UpdateLocalMatrix();
    void UpdateProjectionMatrix();
    Eigen::Vector3f location;
    Eigen::Quaternionf rotation;
    Eigen::Matrix4f local_matrix;
    Eigen::Matrix4f local_matrix_inv;
    Eigen::Matrix4f projection_matrix;
    float right;
    float left;
    float near;
    float far;
    float top;
    float bottom;
};


#endif