#ifndef __TSUBAKI_INITIALIZER__
#define __TSUBAKI_INITIALIZER__

#include <utility/config.h>
#include <utility/basic.h>


enum class E_INIT_ERROR{
    NONE_ERROR = 0,
    GLFW_INIT_ERROR = 1,
    GLAD_INIT_ERROR = 2,
};

class Initializer{
public:
    static void InitEngine();
    static bool IsInit();
    static void EndEngine();
    Initializer();
    virtual ~Initializer();
private:
    static bool is_init;
};

#endif