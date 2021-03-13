// #include <iostream>
// #include <glad/glad.h>
// #include <glfw3.h>
// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>
// #include <string>
// int main()
// {
// 	std::string path = "C:\\BlenderOutput\\Miku\\miku_ver4.fbx";
// 	Assimp::Importer importer;
// 	const aiScene* scene = importer.ReadFile(path.c_str(),aiProcess_Triangulate | aiProcess_FlipUVs); 
// 	aiMaterial* material = scene->mMaterials[0];
// 	if(!glfwInit())
// 	{
// 		return -1;
// 	}
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
// 	GLFWwindow* window = glfwCreateWindow(1920,1080,"TSUBAKI RENDER",NULL,NULL);
// 	if(!window)
// 	{
// 		glfwTerminate();
// 		return -2;
// 	}
// 	glfwMakeContextCurrent(window);
// 	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
// 	{
// 		std::cout << "Failed to initialize GLAD" << std::endl;
// 		return -1;
// 	}
// 	GLfloat color = 0.0;
// 	GLfloat seed = 0.0;
// 	GLfloat delta = 0.1;
// 	while(!glfwWindowShouldClose(window))
// 	{
// 		color = (sin(seed)+1.0f)*0.5f;
// 		seed+=delta;
// 		glClearColor(color,color,color,1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT);
// 		glfwSwapBuffers(window);
// 		glfwPollEvents();

// 	}
// 	glfwTerminate();
// 	std::cout << "fuck world..." << std::endl;
// 	return 0;
// }

#include <window/window.h>
#include <utility/initializer.h>
#include <Eigen/Core>
#include <cmath>

int main(int argc,char** argv)
{
	Initializer::InitEngine();
	Window* curr_window = new Window();
	curr_window->SetAsCurrentWindow();
	Eigen::Vector4f clear_color = Eigen::Vector4f(0.0f,0.0f,0.0f,1.0f);
	Eigen::Vector4f clear_color_add =  Eigen::Vector4f(0.01f,0.01f,0.01f,0.0f);
	while(curr_window->GetCurrFrameCount()<1000)
	{
		clear_color = clear_color + clear_color_add;
		std::cout << "Frame Count : " <<curr_window->GetCurrFrameCount() << std::endl;
		std::cout << "FPS : " <<1.0f/curr_window->GetCurrDeltaTime()<<std::endl;
		curr_window->UpdateFrame(sin(clear_color[0]), sin(clear_color[1]), sin(clear_color[2]), (clear_color[3]));
	}
	curr_window->CloseWindow();
	Initializer::EndEngine();
	return 0;
}