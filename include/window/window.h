#ifndef __TSUBAKI_WINDOW__
#define __TSUBAKI_WINDOW__

#include <utility/config.h>
#include <utility/basic.h>
#include <utility/initializer.h>
#include <Eigen/Core>

enum class E_WINDOW_ERROR
{
    NONE_ERROR = 0,
    NONE_INIT_ERROR = 1,
    WINDOW_INIT_ERROR = 2,
};

extern unsigned int WINDOW_WIDTH;
extern unsigned int WINDOW_HEIGHT;
extern const char WINDOW_TITLE[];

class Window{
public:

    static Window* GetWindowInstance();

    void SetAsCurrentWindow();

    void RefreshFrame(float R=0.0f,float G=0.0f,float B=0.0f,float A=1.0f);

    void UpdateStatus();

    void SwapBuffer();
    
    bool IsInit();

    unsigned long long int GetCurrFrameCount();

    double GetCurrDeltaTime();

    void SetDepthTest(bool flag);
    
    void CloseWindow();

    bool IsPressKey(int key);

    void GetMouseMove(float& mouse_move_x,float& mouse_move_y);

    virtual ~Window();    

private:
    Window();

    static Window* window_instance;

    GLFWwindow* window;

    bool is_init;

    unsigned long long int frame_count;

    double render_time;

    double delta_time;

    double mouse_center_x,mouse_center_y,mouse_x,mouse_y;

};


#endif