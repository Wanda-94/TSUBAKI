#ifndef __TSUBAKI_BASIC__
#define __TSUBAKI_BASIC__


#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

#ifdef WIN32
    #include <time.h>
#else
    //#include <sys/time.h>
#endif

const double PI = (3.1415926);

class Timer{
public:
    Timer();
    static float GetCurrTime();
private:
    static float start_time;
    static bool is_first;
};


enum class ObjectType{
    OBJECT,
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    AMBIENT_LIGHT,
    CAMERA,
    ACTOR
};

enum class ResourceType{
    SHADER,
    TEXTURE,
    MATERIAL,
    MESH
};

enum class DataType{
    CHAR = 0,
    INT,
    UINT,
    LONGLONGINT,
    FLOAT,
    DOUBLE,
    STRING
};

enum class DataFormatType{
    R_UC = 0,
    RGB_UC = 1,
    RGBA_UC = 2
};


#endif