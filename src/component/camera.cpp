#include <component/camera.h>

Camera::Camera():right(-100.0f),left(100.0f),near(0.01f),far(10000.0f),top(100.0f),bottom(0.0f)
{
    location = Eigen::Vector3f(0.0f,0.0f,0.0f);
    rotation = Eigen::Quaternionf(1.0f,0.0f,0.0f,0.0f);
    UpdateLocalMatrix();
    UpdateProjectionMatrix();
}
Camera::~Camera()
{

}
void Camera::SetLocation(const Eigen::Vector3f& new_location)
{
    location = new_location;
    UpdateLocalMatrix();
}
void Camera::SetRotation(const Eigen::Quaternionf& new_rotation)
{
    rotation = new_rotation;
}
void Camera::UpdateLocalMatrix()
{
    Eigen::Matrix4f to_local_matrix = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f to_local_matrix_inv = to_local_matrix;
    Eigen::Matrix3f rotation_matrix = rotation.toRotationMatrix();
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            to_local_matrix(i,j) = rotation_matrix(i,j);
            to_local_matrix_inv(i,j) = rotation_matrix(j,i);
        }
    }
    to_local_matrix(0,3) = location.x();
    to_local_matrix(1,3) = location.y();
    to_local_matrix(2,3) = location.z();
    to_local_matrix_inv(0,3) = -location.x();
    to_local_matrix_inv(1,3) = -location.y();
    to_local_matrix_inv(2,3) = -location.z();
    local_matrix = to_local_matrix;
    local_matrix_inv = to_local_matrix_inv;
}
void Camera::UpdateProjectionMatrix()
{
    Eigen::Matrix4f new_projection_matrix;
    new_projection_matrix(0,0) = 2.0f*near/(right-left);
    new_projection_matrix(0,1) = 0.0f;
    new_projection_matrix(0,2) = (right+left)/(right-left);
    new_projection_matrix(0,3) = 0.0f;
    new_projection_matrix(1,0) = 0.0f;
    new_projection_matrix(1,1) = 2.0f*near/(top-bottom);
    new_projection_matrix(1,2) = (top+bottom)/(top-bottom);
    new_projection_matrix(1,3) = 0.0f;
    new_projection_matrix(2,0) = 0.0f;
    new_projection_matrix(2,1) = 0.0f;
    new_projection_matrix(2,2) = (far+near)/(near-far);
    new_projection_matrix(2,3) = (2.0f*far*near)/(near-far);
    new_projection_matrix(3,0) = 0.0f;
    new_projection_matrix(3,1) = 0.0f;
    new_projection_matrix(3,2) = -1.0f;
    new_projection_matrix(3,3) = 0.0f;
    projection_matrix = new_projection_matrix;
}

Eigen::Matrix4f Camera::GetToLocalMatrix()
{
    return local_matrix_inv;
}

Eigen::Matrix4f Camera::GetProjectionMatrix()
{
    return projection_matrix;
}