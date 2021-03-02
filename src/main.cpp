#include <iostream>
#include "glad/glad.h"
#include "glfw3.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <string>
int main()
{
	std::string path = "C:\\WorkSpace\\VS\\Engine\\TSUBAKI\\source\\untitled.fbx";
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path.c_str(),aiProcess_Triangulate | aiProcess_FlipUVs); 
	if(!glfwInit())
	{
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(1920,1080,"TSUBAKI RENDER",NULL,NULL);
	if(!window)
	{
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	GLfloat color = 0.0;
	GLfloat seed = 0.0;
	GLfloat delta = 0.1;
	while(!glfwWindowShouldClose(window))
	{
		color = (sin(seed)+1.0f)*0.5f;
		seed+=delta;
		glClearColor(color,color,color,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	std::cout << "fuck world..." << std::endl;
	return 0;
}