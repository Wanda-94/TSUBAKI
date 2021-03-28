#include <component/camera.h>

Camera::Camera():near(1.0f),far(10000.0f),size(1.0f),move_speed(10.0f),Object(ObjectType::CAMERA)
{
    ratio = (WINDOW_WIDTH)/((float)WINDOW_HEIGHT);
    UpdateToLocalMatrix();
    UpdateProjectionMatrix();
    Controller::InsertCamera(GetObjectID());
}

Camera::Camera(const std::string& init_name):near(1.0f),far(10000.0f),size(1.0f),Object(init_name,ObjectType::CAMERA)
{
    ratio = (WINDOW_WIDTH)/((float)WINDOW_HEIGHT);
    UpdateToLocalMatrix();
    UpdateProjectionMatrix();
    Controller::InsertCamera(GetObjectID());
}

Camera::~Camera()
{
    Controller::RemoveCamera(GetObjectID());
}

void Camera::Update(float delta_time)
{
    std::cout<<"camera"<<std::endl;
    Window* curr_window = Window::GetWindowInstance();
    float mouse_move_x,mouse_move_y;
    curr_window->GetMouseMove(mouse_move_x,mouse_move_y);
    float angle_x = -((mouse_move_x*90.0f)*PI/180.0f);
    float angle_y = (mouse_move_y*90.0f)*PI/180.0f;
    SetRotation(GetRotation()*Eigen::Quaternionf(cos(angle_x),0.0f,sin(angle_x),0.0f));
    SetRotation(GetRotation()*Eigen::Quaternionf(cos(angle_y),sin(angle_y),0.0f,0.0f));
    if(curr_window->IsPressKey(GLFW_KEY_W))
    {
        SetLocation(GetLocation()+delta_time*move_speed*(GetRotation()*Eigen::Vector3f(0.0f,0.0f,1.0f)));
    }
    if(curr_window->IsPressKey(GLFW_KEY_S))
    {
        SetLocation(GetLocation()+delta_time*move_speed*(GetRotation()*Eigen::Vector3f(0.0f,0.0f,-1.0f)));
    }
    if(curr_window->IsPressKey(GLFW_KEY_A))
    {
        SetLocation(GetLocation()+delta_time*move_speed*(GetRotation()*Eigen::Vector3f(1.0f,0.0f,0.0f)));
    }
    if(curr_window->IsPressKey(GLFW_KEY_D))
    {
        SetLocation(GetLocation()+delta_time*move_speed*(GetRotation()*Eigen::Vector3f(-1.0f,0.0f,0.0f)));
    }
}

void Camera::SetLocation(const Eigen::Vector3f& new_location)
{
    Object::SetLocation(new_location);
    UpdateToLocalMatrix();
}

void Camera::SetRotation(const Eigen::Quaternionf& new_rotation)
{
    Object::SetRotation(new_rotation);
    UpdateToLocalMatrix();
}

void Camera::SetMoveSpeed(float new_move_speed)
{
    move_speed = new_move_speed;
}

void Camera::SetAsCurrCamera()
{
    Controller::SetCurrCamera(GetObjectID());
}

float Camera::GetMoveSpeed()
{
    return move_speed;
}

Eigen::Vector3f Camera::GetLocation() const
{
    return Object::GetLocation();
}

Eigen::Quaternionf Camera::GetRotation() const
{
    return Object::GetRotation();
}

Eigen::Matrix4f Camera::GetTransformMatrix() const
{
    return Object::GetTransformMatrix();
}

void Camera::UpdateToLocalMatrix()
{
    Eigen::Matrix4f new_to_local_matrix = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f local_matrix = Object::GetTransformMatrix();
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            new_to_local_matrix(i,j) = local_matrix(j,i);
        }
    }
    new_to_local_matrix(0,3) = -local_matrix(0,3)*new_to_local_matrix(0,0)-local_matrix(1,3)*new_to_local_matrix(0,1)-local_matrix(2,3)*new_to_local_matrix(0,2);
    new_to_local_matrix(1,3) = -local_matrix(0,3)*new_to_local_matrix(1,0)-local_matrix(1,3)*new_to_local_matrix(1,1)-local_matrix(2,3)*new_to_local_matrix(1,2);
    new_to_local_matrix(2,3) = -local_matrix(0,3)*new_to_local_matrix(2,0)-local_matrix(1,3)*new_to_local_matrix(2,1)-local_matrix(2,3)*new_to_local_matrix(2,2);
    to_local_matrix = new_to_local_matrix;
}

void Camera::UpdateProjectionMatrix()
{
    Eigen::Matrix4f new_projection_matrix;
    new_projection_matrix(0,0) = (-near)/(size);
    new_projection_matrix(0,1) = 0.0f;
    new_projection_matrix(0,2) = 0.0f;
    new_projection_matrix(0,3) = 0.0f;
    new_projection_matrix(1,0) = 0.0f;
    new_projection_matrix(1,1) = (near)*(ratio)/(size);
    new_projection_matrix(1,2) = 0.0f;
    new_projection_matrix(1,3) = 0.0f;
    new_projection_matrix(2,0) = 0.0f;
    new_projection_matrix(2,1) = 0.0f;
    new_projection_matrix(2,2) = (far+near)/(far-near);
    new_projection_matrix(2,3) = (2.0f*far*near)/(near-far);
    new_projection_matrix(3,0) = 0.0f;
    new_projection_matrix(3,1) = 0.0f;
    new_projection_matrix(3,2) = 1.0f;
    new_projection_matrix(3,3) = 0.0f;
    projection_matrix = new_projection_matrix;
}

Eigen::Matrix4f Camera::GetToLocalMatrix() const
{
    return to_local_matrix;
}

Eigen::Matrix4f Camera::GetProjectionMatrix() const
{
    return projection_matrix;
}

void Camera::SetSize(const float new_size)
{
    size = new_size;
    UpdateProjectionMatrix();
}