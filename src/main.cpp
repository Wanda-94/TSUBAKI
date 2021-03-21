#include <window/window.h>
#include <utility/initializer.h>
#include <Eigen/Core>
#include <cmath>
#include <component/transform.h>
#include <component/object.h>
#include <utility/controller.h>
#include <utility/importer.h>
#include <component/shader.h>

int main(int argc,char** argv)
{
	Initializer::InitEngine();
	Window* curr_window = new Window();
	curr_window->SetAsCurrentWindow();
	Eigen::Vector4f clear_color = Eigen::Vector4f(0.0f,0.0f,0.0f,1.0f);
	Eigen::Vector4f clear_color_add =  Eigen::Vector4f(0.01f,0.01f,0.01f,0.0f);
	// Transform t1;
	// Eigen::AngleAxisf r = Eigen::AngleAxisf(45.0f,Eigen::Vector3f(1.0f,0.0f,0.0f));
	// Eigen::Quaternionf rq = Eigen::Quaternionf(r);
	// Transform t2(Eigen::Vector3f(1.0f,2.0f,3.0f),rq,Eigen::Vector3f(3.0f,4.0f,5.0f));
	// t1.SetTransformMatrix(t2.GetTransformMatrix());
	// Object* obj_1 = new Object();
	// Object* obj_2 = new Object();
	// Object* obj_3 = new Object();
	//Eigen::Vector3f v(1.0, 2.0, 3.0);
	//std::cout << sizeof(Eigen::Vector3f) << std::endl;

	Shader* shader = new Shader("brdf","C:/WorkSpace/VS/Engine/TSUBAKI/shader/brdf");

	Vertex v1;
	v1.SetPosition(-1.0f,0.0f,0.0f);
	Vertex v2;
	v2.SetPosition(1.0f,-1.0f,0.0f);
	Vertex v3;
	v3.SetPosition(1.0f,1.0f,0.0f);
	std::vector<Vertex> vertices({v1,v2,v3});
	std::vector<unsigned int> indices({0,1,2});

	Mesh* mesh = new Mesh("Triangle",vertices,indices);

	// std::string TBKpath = "C:/BlenderOutput/Addones/tsubaki.tbk";
	// TBKScene* scene = new TBKScene();
	// Importer::LoadTBK(TBKpath,scene);

	std::vector<Mesh*> mesh_list;

	// for(int i=0;i<Importer::GetMeshNumFromTBKScene(scene);i++)
	// {
	// 	mesh_list.push_back(Importer::GetMeshFromTBKScene(scene,i));
	// }

	mesh_list.push_back(mesh);

	while(curr_window->GetCurrFrameCount()<1000)
	{
		clear_color = clear_color + clear_color_add;
		//std::cout << "Frame Count : " <<curr_window->GetCurrFrameCount() << std::endl;
		//std::cout << "FPS : " <<1.0f/curr_window->GetCurrDeltaTime()<<std::endl;
		curr_window->UpdateFrame(sin(clear_color[0]), sin(clear_color[1]), sin(clear_color[2]), (clear_color[3]));
		//Controller::UpdateObject(0.0f);

		/////////////
		Eigen::Matrix4f identity = Eigen::Matrix4f::Identity();
		Eigen::Matrix4f translate = identity;
		translate(0,3) = 0.5f;
		shader->UseShader();
		shader->SetUniformMatrix4x4("transform_matrix",translate);
		shader->SetUniformMatrix4x4("camera_matrix",identity);
		shader->SetUniformMatrix4x4("projection_matrix",identity);
		for(int i=0;i<mesh_list.size();i++)
		{
			mesh_list[i]->DrawMesh();
		}

		curr_window->SwapBuffer();
		////////////
	}
	curr_window->CloseWindow();
	// 
	//std::string path = "C:\\BlenderOutput\\Miku\\miku_ver5.fbx";
	//std::string path = "C:\\BlenderOutput\\JiuTun\\JiuTun.fbx";
	// std::string path = "C:\\BlenderOutput\\Miku\\miku_ver3_armature_ver2.fbx";

	Initializer::EndEngine();
	return 0;
}