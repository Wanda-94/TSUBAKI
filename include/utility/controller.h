#ifndef __TSUBAKI_CONTROLLER__
#define __TSUBAKI_CONTROLLER__

#include <unordered_map>
#include <stack>


class Object;

class Controller{
public:
    static int InsertObject(const std::string& name,const Object* object);
    static void RemoveObject(const int ID);
    static void UpdateObject(float delta_time);
    virtual ~Controller();
private:
    Controller();
    static Controller* GetController();
    int GenID();
    int InsertObject_(const std::string& name,const Object* object);
    void RemoveObejct_(const int ID);
    void UpdateObject_(float delta_time);
    static Controller* controller;
    std::unordered_map<int,std::pair<std::string,Object*> > object_resource_list;
    std::stack<unsigned int> ID_stack;
};


#endif