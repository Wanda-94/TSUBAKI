#include <component/object.h>

Object::Object()
{
    this->transform = new Transform();
    //ID NAME
    this->name = "None";

    this->type = ObjectType::OBJECT;

    this->ID = Controller::InsertObject(this);

    this->local_matrix = Eigen::Matrix4f::Identity();

    this->parent = nullptr;
    
    this->childs.resize(0);
}

Object::Object(const std::string init_name)
{
    this->transform = new Transform();
    //ID
    this->name = init_name;

    this->type = ObjectType::OBJECT;

    this->ID = Controller::InsertObject(this);

    this->local_matrix = Eigen::Matrix4f::Identity();

    this->parent = nullptr;
    
    this->childs.resize(0);
}

Object::Object(const std::string init_name,const ObjectType& init_object_type)
{
    this->transform = new Transform();
    //ID
    this->name = init_name;

    this->type = init_object_type;

    this->ID = Controller::InsertObject(this);

    this->local_matrix = Eigen::Matrix4f::Identity();

    this->parent = nullptr;
    
    this->childs.resize(0);
}

Object::Object(const ObjectType& init_object_type)
{
    this->transform = new Transform();
    //ID NAME
    this->name = "None";

    this->type = init_object_type;

    this->ID = Controller::InsertObject(this);

    this->local_matrix = Eigen::Matrix4f::Identity();

    this->parent = nullptr;
    
    this->childs.resize(0);
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

    UpdateLocalMatrix();

    UpdateChilds();
}

void Object::SetLocation(const Eigen::Vector3f& new_location)
{
    this->transform->SetLocation(new_location);

    UpdateLocalMatrix();

    UpdateChilds();
}

void Object::SetTransform(const Transform& new_transform)
{
    *(this->transform) = new_transform;

    UpdateLocalMatrix();

    UpdateChilds();
}

void Object::SetRotation(const Eigen::Quaternionf& new_rotation)
{
    this->transform->SetRotation(new_rotation);

    UpdateLocalMatrix();

    UpdateChilds();
}

void Object::SetScale(const Eigen::Vector3f& new_scale)
{
    this->transform->SetScale(new_scale);

    UpdateLocalMatrix();

    UpdateChilds();
}

void Object::AttachToParent(Object* new_parent)
{
    DetachFromParent();
    new_parent->AddChild(this);
    this->parent = new_parent;
    UpdateLocalMatrix();
}

void Object::DetachFromParent()
{
    if(this->parent!=nullptr)
    {
        GetParent()->RemoveChild(this);
        this->parent = nullptr;
    }
}

Object* Object::GetParent()
{
    return this->parent;
}

void Object::AddChild(Object* new_child)
{
    this->childs.push_back(new_child);
}

void Object::RemoveChild(Object* rm_child)
{
    for(auto i = this->childs.begin();i!=this->childs.end();i++)
    {
        if((*i)==rm_child)
        {
            this->childs.erase(i);
            break;
        }
    }
}

int Object::GetChildNum()
{
    return this->childs.size();
}

Object* Object::GetChild(int index)
{
    assert(index<this->childs.size());
    return this->childs[index];
}

void Object::UpdateLocalMatrix()
{
    if(parent!=nullptr)
    {
        local_matrix = (parent->GetTransformMatrix().inverse())*GetTransformMatrix(); 
    }
}

void Object::UpdateChilds(const Eigen::Matrix4f& parent_curr_transform_matrix)
{
    SetTransformMatrix(parent_curr_transform_matrix*this->local_matrix);
    // for(int i=0;i<this->childs.size();i++)
    // {
    //     this->childs[i]->UpdateChilds(GetTransformMatrix());
    // }
}

void Object::UpdateChilds()
{
    for(int i=0;i<this->childs.size();i++)
    {
        this->childs[i]->UpdateChilds(GetTransformMatrix());
    }
}