#ifndef __TSUBAKI_RESOURCE__
#define __TSUBAKI_RESOURCE__

#include <string>
#include <utility/basic.h>

class Resource{
public:
    Resource();
    Resource(const std::string label);
    Resource(const ResourceType& init_type);
    Resource(const std::string label,const ResourceType& init_type);
    ResourceType GetResourceType();
    std::string GetLabel();
    int GetID();
private:
    int ID;
    std::string label;
    ResourceType resource_type;
};

#endif