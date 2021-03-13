#include <utility/basic.h>

float Timer::start_time = 0.0f;

bool Timer::is_first = true;

float Timer::GetCurrTime()
{
    float time = 0.0f;

    if(is_first==true)
    {

        start_time =  clock()*0.001;

        is_first = false;

    }

    clock_t curr_time = clock();

    time = curr_time*0.001 - start_time;

    return time;
}