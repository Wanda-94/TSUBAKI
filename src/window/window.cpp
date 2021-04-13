#include <window/window.h>

Window* Window::window_instance = nullptr;

Window* Window::GetWindowInstance()
{
    if(window_instance==nullptr)
    {
        window_instance = new Window();
    }
    return window_instance;
}

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

        background_color = Eigen::Vector4f(1.0f,1.0f,1.0f,1.0f);
    }
}

void Window::SetAsCurrentWindow()
{
    if(IsInit()&&window!=nullptr)
    {

        glfwMakeContextCurrent(window);

        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);

        glfwGetCursorPos(window,&mouse_center_x,&mouse_center_y);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();(void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window,true);
        ImGui_ImplOpenGL3_Init("#version 450 core");
    }
}

void Window::SetDepthTest(bool flag)
{

    if(flag == true)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
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

void Window::DealInputEvent()
{
    glfwPollEvents();
}

void Window::RefreshGUIFrame()
{
    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    {
        ImGui::Begin("Window Setting");
        ImGui::ColorEdit4("background color",background_color.data());
        ImGui::End();
    }
}

void Window::RefreshFrame()
{

    UpdateStatus();

    glClearColor(background_color[0],background_color[1],background_color[2],
    background_color[3]);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        //glClearDepth(-1000.0);
 
}

void Window::SwapBuffer()
{

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    mouse_center_x = mouse_x;

    mouse_center_y = mouse_y;

}
void Window::UpdateStatus()
{

    float curr_time = Timer::GetCurrTime();

    delta_time = curr_time - render_time;

    render_time = curr_time;

    frame_count = frame_count + 1; 

    glfwGetCursorPos(window,&mouse_x,&mouse_y);

    
}

void Window::CloseWindow()
{

    if(window!=nullptr)
    {

        glfwDestroyWindow(window);

        window = nullptr;
    
    }

}

bool Window::IsPressKey(int key)
{
    int status = glfwGetKey(window,key);
    return (status == GLFW_PRESS);
}

void Window::GetMouseMove(float& mouse_move_x,float& mouse_move_y)
{
    mouse_move_x = (mouse_x - mouse_center_x)/(WINDOW_WIDTH);
    mouse_move_y = (mouse_y - mouse_center_y)/(WINDOW_HEIGHT);
}

Window::~Window()
{
    if(window!=nullptr)
    {
        CloseWindow();
    }
}