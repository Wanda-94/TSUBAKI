#include <window/window.h>

Window::Window():is_init(false),frame_count(0),render_time(0.0f),delta_time(0.0f)
{
    E_WINDOW_ERROR error = E_WINDOW_ERROR::NONE_ERROR;
    
    if(Initializer::IsInit() == false)
    {
        
        error = E_WINDOW_ERROR::NONE_INIT_ERROR;

        goto end;

    }

    window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_TITLE,nullptr,nullptr);

    if(window==nullptr)
    {

        error = E_WINDOW_ERROR::WINDOW_INIT_ERROR;

        goto end;

    }

end:
    if(error != E_WINDOW_ERROR::NONE_ERROR)
    {
        //...
        std::cout<<"window initial failed..."<<std::endl;
        std::cout<<"error code is :"<<(int)error<<std::endl;
    }
    else
    {
        is_init = true;
    }

}

void Window::SetAsCurrentWindow()
{

    if(IsInit()&&window!=nullptr)
    {

        glfwMakeContextCurrent(window);

    }
}

bool Window::IsInit()
{

    return is_init;

}


unsigned long long int Window::GetCurrFrameCount()
{

    return frame_count;

}

double Window::GetCurrDeltaTime()
{

    return delta_time;
}

void Window::UpdateFrame(float R,float G,float B,float A)
{

    if(IsInit())
    {

        UpdateStatus();

        glClearColor(R,G,B,A);

        glClear(GL_COLOR_BUFFER_BIT);

        if(window!=nullptr)
        {

            glfwSwapBuffers(window);

        }

        glfwPollEvents();

    }

}

void Window::UpdateStatus()
{

    float curr_time = Timer::GetCurrTime();

    delta_time = curr_time - render_time;

    render_time = curr_time;

    frame_count = frame_count + 1; 

}

void Window::CloseWindow()
{

    if(window!=nullptr)
    {

        glfwDestroyWindow(window);

        window = nullptr;
    
    }

}

Window::~Window()
{
    if(window!=nullptr)
    {
        CloseWindow();
    }
}