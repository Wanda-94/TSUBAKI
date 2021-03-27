#include <component/object.h>

Object::Object()
{
    this->transform = new Transform();
    //ID NAME
    this->name = "None";

    this->type = ObjectType::OBJECT;

    this->ID = Controller::InsertObject(this);
}

Object::Object(const std::string init_name)
{
    this->transform = new Transform();
    //ID
    this->name = init_name;

    this->type = ObjectType::OBJECT;

    this->ID = Controller::InsertObject(this);
}

Object::Object(const std::string init_name,const ObjectType& init_object_type)
{
    this->transform = new Transform();
    //ID
    this->name = init_name;

    this->type = init_object_type;

    this->ID = Controller::InsertObject(this);
}

Object::Object(const ObjectType& init_object_type)
{
    this->transform = new Transform();
    //ID NAME
    this->name = "None";

    this->type = init_object_type;

    this->ID = Controller::InsertObject(this);
}

Object::~Object()
{
    if(transform!=nullptr)
    {
        Controller::RemoveObject(this->ID);
        delete this->transform;
    }
}

unsigned int Object::GetObjectID() const
{
    return this->ID;
}

std::string Object::GetObjectName() const
{
    return this->name;
}

void Object::Update(float delta_time)
{
    int a = 0;
    std::cout<<"object update"<<std::endl;
    return;
}

ObjectType Object::GetObjectType() const
{
    return this->type;
}

Transform* Object::GetTransform() const
{
    return this->transform;
}

Transform Object::GetTransformCopy() const
{
    return *(this->transform);
}

Eigen::Matrix4f Object::GetTransformMatrix() const
{
    return this->transform->GetTransformMatrix();
}

Eigen::Vector3f Object::GetLocation() const
{
    return this->transform->GetLocation();
}

Eigen::Quaternionf Object::GetRotation() const
{
    return this->transform->GetRotaion();
}

Eigen::Vector3f Object::GetScale() const
{
    return this->transform->GetScale();
}

void Object::SetTransformMatrix(const Eigen::Matrix4f& new_transform_matrix)
{
    this->transform->SetTransformMatrix(new_transform_matrix);
}

void Object::SetLocation(const Eigen::Vector3f& new_location)
{
    this->transform->SetLocation(new_location);
}

void Object::SetTransform(const Transform& new_transform)
{
    *(this->transform) = new_transform;
}

void Object::SetRotation(const Eigen::Quaternionf& new_rotation)
{
    this->transform->SetRotation(new_rotation);
}

void Object::SetScale(const Eigen::Vector3f& new_scale)
{
    this->transform->SetScale(new_scale);
}
