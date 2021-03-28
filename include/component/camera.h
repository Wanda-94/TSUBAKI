#ifndef __TSUBAKI_CAMERA__
#define __TSUBAKI_CAMERA__

#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <component/object.h>
#include <utility/config.h>
#include <utility/basic.h>
#include <window/window.h>

extern unsigned int WINDOW_WIDTH;
extern unsigned int WINDOW_HEIGHT;

class Camera : public Object{
public:
    Camera();
    Camera(const std::string& init_name);
    ~Camera();
    virtual void Update(float delta_time);
    void SetLocation(const Eigen::Vector3f& new_location);
    void SetRotation(const Eigen::Quaternionf& new_rotation);
    void SetSize(const float new_size);
    void SetMoveSpeed(float new_move_speed);
    void SetAsCurrCamera();
    float GetMoveSpeed();
    Eigen::Vector3f GetLocation() const;
    Eigen::Quaternionf GetRotation() const;
    Eigen::Matrix4f GetTransformMatrix() const;
    Eigen::Matrix4f GetToLocalMatrix() const;
    Eigen::Matrix4f GetProjectionMatrix() const;
private:
    void UpdateToLocalMatrix();
    void UpdateProjectionMatrix();

    Eigen::Matrix4f to_local_matrix;
    Eigen::Matrix4f projection_matrix;
    float size;//window size
    float ratio;//width/height
    float near;
    float far;

    float move_speed;

};


#endif