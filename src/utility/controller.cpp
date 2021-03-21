#include <utility/controller.h>
#include <component/object.h>

Controller* Controller::controller = nullptr;

Controller* Controller::GetController()
{
    if(controller==nullptr)
    {
        controller = new Controller();
    }
    return controller;
}
int Controller::InsertObject_(const std::string& name,const Object* object)
{
    int ID = GenID();
    object_resource_list[ID] = std::pair<std::string,Object*>(const_cast<std::string&>(name),const_cast<Object*>(object));
    return ID;
}
void Controller::RemoveObejct_(const int ID)
{
    if(object_resource_list.find(ID)!=object_resource_list.end())
    {
        object_resource_list.erase(ID);
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
    if(controller!=nullptr)
    {
        delete controller;
    }
}
Controller::Controller()
{
    ID_stack.push(0);
}
void Controller::UpdateObject_(float delta_time)
{
    for(auto i = object_resource_list.begin();i!=object_resource_list.end();i++)
    {
        Object* object = i->second.second;
        object->Update(delta_time);
    }
}
int Controller::InsertObject(const std::string& name,const Object* object)
{
    return GetController()->InsertObject_(name,object); 
}
void Controller::RemoveObject(const int ID)
{
    return GetController()->RemoveObejct_(ID);
}
void Controller::UpdateObject(float delta_time)
{
    return GetController()->UpdateObject_(delta_time);
}