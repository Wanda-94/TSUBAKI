#include <component/object.h>

Object::Object()
{
    transform = new Transform();
    //ID NAME
    std::string name = "None";

    ID = Controller::InsertObject(name,this);
}
Object::Object(const std::string init_name)
{
    transform = new Transform();
    //ID
    name = init_name;

    ID = Controller::InsertObject(name,this);
}
Object::~Object()
{
    if(transform!=nullptr)
    {
        Controller::RemoveObject(ID);
        delete transform;
    }
}
void Object::Update(float delta_time)
{
    int a = 0;
    std::cout<<"object update"<<std::endl;
    return;
}
Transform* Object::GetTransform()
{
    return transform;
}
Transform Object::GetTransformCopy()
{
    return *transform;
}
void Object::SetLocation(const Eigen::Vector3f& new_location)
{
    transform->SetLocation(new_location);
}
void Object::SetTransform(const Transform& new_transform)
{
    *transform = new_transform;
}
void Object::SetRotation(const Eigen::Quaternionf& new_rotation)
{
    transform->SetRotation(new_rotation);
}
void Object::SetScale(const Eigen::Vector3f& new_scale)
{
    transform->SetScale(new_scale);
}
