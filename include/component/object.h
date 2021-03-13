#ifndef __TSUBAKI_OBJECT__
#define __TSUBAKI_OBJECT__

#include <string>
#include <component/transform.h>

class Object{
public:
    Object();
    virtual ~Object();

private:
    unsigned int ID;
    std::string name;
};


#endif