#include <component/transform.h>

Transform::Transform()
{
    this->location = Eigen::Vector3f(0.0f,0.0f,0.0f);
    this->scale = Eigen::Vector3f(1.0f,1.0f,1.0f);
    this->rotation = Eigen::Quaternionf(1.0f,0.0f,0.0f,0.0f);
    UpdateTransformMatrix();
}
Transform::Transform(const Transform& t)
{
    this->location = t.GetLocation();
    this->scale = t.GetScale();
    this->rotation = t.GetRotaion();
    UpdateTransformMatrix();
}
Transform& Transform::operator=(const Transform& t)
{
    this->location = t.GetLocation();
    this->scale = t.GetScale();
    this->rotation = t.GetRotaion();
    UpdateTransformMatrix();
    return (*this);
}
Transform::Transform(const Eigen::Vector3f& init_location,const Eigen::Quaternionf& init_rotation,const Eigen::Vector3f& init_scale)
{
    this->location = init_location;
    this->rotation = init_rotation;
    this->scale = init_scale;
    UpdateTransformMatrix();
}
Transform::~Transform()
{

}
void Transform::SetLocation(const Eigen::Vector3f& new_location)
{
    this->location = new_location;
    UpdateTransformMatrix();
}
void Transform::SetRotation(const Eigen::Quaternionf& new_rotation)
{
    this->rotation = new_rotation;
    UpdateTransformMatrix();
}
void Transform::SetScale(const Eigen::Vector3f& new_scale)
{
    this->scale = new_scale;
    UpdateTransformMatrix();
}
void Transform::SetTransformMatrix(const Eigen::Matrix4f& new_transform_matrix)
{
    this->transform_matrix = new_transform_matrix;
    UpdateStatus();
}
Eigen::Vector3f Transform::GetLocation() const
{
    return this->location;
}
Eigen::Vector3f& Transform::GetLocation()
{
    return this->location;
}
Eigen::Quaternionf Transform::GetRotaion() const
{
    return this->rotation;
}
Eigen::Vector3f Transform::GetScale() const
{
    return this->scale;
}
Eigen::Matrix4f Transform::GetTransformMatrix() const
{
    return this->transform_matrix;
}
void Transform::UpdateTransformMatrix()
{
    Eigen::Matrix3f rotation_matrix = this->rotation.toRotationMatrix();
    this->transform_matrix(0,0) = rotation_matrix(0,0)*this->scale[0];
    this->transform_matrix(1,0) = rotation_matrix(1,0)*this->scale[0];
    this->transform_matrix(2,0) = rotation_matrix(2,0)*this->scale[0];
    this->transform_matrix(0,1) = rotation_matrix(0,1)*this->scale[1];
    this->transform_matrix(1,1) = rotation_matrix(1,1)*this->scale[1];
    this->transform_matrix(2,1) = rotation_matrix(2,1)*this->scale[1];
    this->transform_matrix(0,2) = rotation_matrix(0,2)*this->scale[2];
    this->transform_matrix(1,2) = rotation_matrix(1,2)*this->scale[2];
    this->transform_matrix(2,2) = rotation_matrix(2,2)*this->scale[2];
    this->transform_matrix(0,3) = this->location[0];
    this->transform_matrix(1,3) = this->location[1];
    this->transform_matrix(2,3) = this->location[2];
    this->transform_matrix(3,0) = 0.0f;
    this->transform_matrix(3,1) = 0.0f;
    this->transform_matrix(3,2) = 0.0f;
    this->transform_matrix(3,3) = 1.0f;
}
void Transform::UpdateStatus()
{
    this->location[0] = this->transform_matrix(0,3);
    this->location[1] = this->transform_matrix(1,3);
    this->location[2] = this->transform_matrix(2,3);

    this->scale[0] = sqrtf(transform_matrix(0,0)*transform_matrix(0,0)+transform_matrix(1,0)*transform_matrix(1,0)+transform_matrix(2,0)*transform_matrix(2,0));
    this->scale[1] = sqrtf(transform_matrix(0,1)*transform_matrix(0,1)+transform_matrix(1,1)*transform_matrix(1,1)+transform_matrix(2,1)*transform_matrix(2,1));
    this->scale[2] = sqrtf(transform_matrix(0,2)*transform_matrix(0,2)+transform_matrix(1,2)*transform_matrix(1,2)+transform_matrix(2,2)*transform_matrix(2,2));

    float s0i = 1.0f/scale[0];
    float s1i = 1.0f/scale[1];
    float s2i = 1.0f/scale[2];
    float m00 = transform_matrix(0,0)*s0i;
    float m10 = transform_matrix(1,0)*s0i;
    float m20 = transform_matrix(2,0)*s0i;
    float m01 = transform_matrix(0,1)*s1i;
    float m11 = transform_matrix(1,1)*s1i;
    float m21 = transform_matrix(2,1)*s1i;
    float m02 = transform_matrix(0,2)*s2i;
    float m12 = transform_matrix(1,2)*s2i;
    float m22 = transform_matrix(2,2)*s2i;

    float tr = m00 + m11 + m22;

    float qw,qx,qy,qz;

    if (tr > 0) { 
        float S = sqrt(tr+1.0) * 2; // S=4*qw 
        qw = 0.25 * S;
        qx = (m21 - m12) / S;
        qy = (m02 - m20) / S; 
        qz = (m10 - m01) / S; 
    } else if ((m00 > m11)&(m00 > m22)) { 
        float S = sqrt(1.0 + m00 - m11 - m22) * 2; // S=4*qx 
        qw = (m21 - m12) / S;
        qx = 0.25 * S;
        qy = (m01 + m10) / S; 
        qz = (m02 + m20) / S; 
    } else if (m11 > m22) { 
        float S = sqrt(1.0 + m11 - m00 - m22) * 2; // S=4*qy
        qw = (m02 - m20) / S;
        qx = (m01 + m10) / S; 
        qy = 0.25 * S;
        qz = (m12 + m21) / S; 
    } else { 
        float S = sqrt(1.0 + m22 - m00 - m11) * 2; // S=4*qz
        qw = (m10 - m01) / S;
        qx = (m02 + m20) / S;
        qy = (m12 + m21) / S;
        qz = 0.25 * S;
    }
    
    rotation.w() = qw;
    rotation.x() = qx;
    rotation.y() = qy;
    rotation.z() = qz;
    rotation.normalize();
}