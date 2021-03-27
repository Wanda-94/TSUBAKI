#include <utility/controller.h>
#include <component/object.h>
#include <component/light.h>

Controller* Controller::controller_instance = nullptr;

Controller* Controller::GetController()
{
    if(controller_instance==nullptr)
    {
        controller_instance = new Controller();
    }
    return controller_instance;
}

int Controller::InsertObject_(const Object* object)
{
    int ID = GenID();
    object_map[ID] = const_cast<Object*>(object);
    return ID;
}

void Controller::RemoveObejct_(const int ID)
{
    if(object_map.find(ID)!=object_map.end())
    {
        object_map.erase(ID);
        ID_stack.push(ID);
    }
}

int Controller::GenID()
{
    int ID;
    if(ID_stack.size()==1)
    {
        ID = ID_stack.top();
        ID_stack.pop();
        ID_stack.push(ID+1);
    }
    else
    {
        ID = ID_stack.top();
        ID_stack.pop();
    }
    return ID;
}

Controller::~Controller()
{
    if(controller_instance!=nullptr)
    {
        delete controller_instance;
    }
}

Controller::Controller()
{
    ID_stack.push(0);
}

void Controller::UpdateObject_(float delta_time)
{
    for(auto i = object_map.begin();i!=object_map.end();i++)
    {
        Object* object = i->second;
        object->Update(delta_time);
    }
}

int Controller::InsertObject(const Object* object)
{
    return GetController()->InsertObject_(object); 
}

void Controller::RemoveObject(const int ID)
{
    return GetController()->RemoveObejct_(ID);
}

void Controller::UpdateObject(float delta_time)
{
    return GetController()->UpdateObject_(delta_time);
}

void Controller::InsertDirectionalLight(const int ID)
{
    GetController()->InsertDirectionalLight_(ID);
}

void Controller::InsertPointLight(const int ID)
{
    GetController()->InsertPointLight_(ID);
}

void Controller::RemoveDirectionalLight(const int ID)
{
    GetController()->RemoveDirectionalLight_(ID);
}

void Controller::RemovePointLight(const int ID)
{
    GetController()->RemovePointLight_(ID);
}

void Controller::InsertDirectionalLight_(const int ID)
{
    this->directional_light_list.push_back(ID);
}

void Controller::InsertPointLight_(const int ID)
{
    this->point_light_list.push_back(ID);
}

void Controller::RemoveDirectionalLight_(const int ID)
{
    for(int i=0;i<directional_light_list.size();i++)
    {
        if(directional_light_list[i]==ID)
        {
            directional_light_list.erase(directional_light_list.begin()+i);
            break;
        }
    }
}

void Controller::RemovePointLight_(const int ID)
{
    for(int i=0;i<point_light_list.size();i++)
    {
        if(point_light_list[i]==ID)
        {
            point_light_list.erase(point_light_list.begin()+i);
            break;
        }
    }
}

int Controller::GetDirectionalLightNum()
{
    return GetController()->directional_light_list.size();
}

int Controller::GetPointLightNum()
{
    return GetController()->point_light_list.size();
}

PointLight* Controller::GetPointLihgt(const int index)
{
    Controller* instance = GetController();
    return (PointLight*)(instance->object_map[instance->point_light_list[index]]);
}

DirectionalLight* Controller::GetDirectionalLight(const int index)
{
    Controller* instance = GetController();
    return (DirectionalLight*)(instance->object_map[instance->directional_light_list[index]]);
}