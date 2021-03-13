#include <utility/initializer.h>

bool Initializer::is_init = false;

void Initializer::InitEngine()
{
    E_INIT_ERROR error = E_INIT_ERROR::NONE_ERROR;

    if(!glfwInit())
    {

        error = E_INIT_ERROR::GLFW_INIT_ERROR;

        goto end;

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,OPENGL_MAJOR_VERSION);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,OPENGL_MINOR_VERSION);

    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(10,10,"init",nullptr,nullptr);

    if(window==nullptr)
    {

        error = E_INIT_ERROR::GLFW_INIT_ERROR;

        goto end;

    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {

        glfwDestroyWindow(window);

        error = E_INIT_ERROR::GLAD_INIT_ERROR;

        goto end;

    }

    glfwDestroyWindow(window);
end:
    if(error!=E_INIT_ERROR::NONE_ERROR)
    {
        //deal some log
        std::cout<<"initializer failed..."<<std::endl;
        std::cout << "error code is :" << (int)error << std::endl;
    }
    else{
        is_init = true;
    }
}

bool Initializer::IsInit()
{
    return is_init;
}

void Initializer::EndEngine()
{
    glfwTerminate();
}