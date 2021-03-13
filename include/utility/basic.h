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

class Timer{
public:
    Timer();
    static float GetCurrTime();
private:
    static float start_time;
    static bool is_first;
};

#endif