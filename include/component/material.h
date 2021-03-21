#ifndef __TSUBAKI_MATERIAL__
#define __TSUBAKI_MATERIAL__

#include <component/shader.h>

class Material{
public:
    Material();
    ~Material();
    void UseMaterial();
private:
    std::string label;
    Shader* shader;
};


#endif