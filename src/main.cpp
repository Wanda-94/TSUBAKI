#include <window/window.h>
#include <utility/initializer.h>
#include <Eigen/Core>
#include <cmath>
#include <component/transform.h>
#include <component/object.h>
#include <utility/controller.h>
#include <utility/importer.h>
#include <component/shader.h>
#include <component/camera.h>
#include <component/light.h>
#include <component/material.h>

int main(int argc,char** argv)
{

	Initializer::InitEngine();
	
	Window* curr_window = Window::GetWindowInstance();
	curr_window->SetAsCurrentWindow();
	curr_window->SetDepthTest(true);

	// Object* obj_1 = new Object();
	// Object* obj_2 = new Object();
	// Object* obj_3 = new Object();
	Camera* camera_0 = new Camera();
	camera_0->SetLocation(Eigen::Vector3f(10.0f,0.0f,100.0f));
	camera_0->SetRotation(Eigen::Quaternionf(0.0f,0.0f,1.0f,0.0f));
	camera_0->SetMoveSpeed(100.0f);

	Camera* camera_1 = new Camera();
	camera_1->SetLocation(Eigen::Vector3f(-10.0f,0.0f,100.0f));
	camera_1->SetRotation(Eigen::Quaternionf(0.0f,0.0f,1.0f,0.0f));
	camera_1->SetMoveSpeed(100.0f);

	Camera* camera_list[2] = {camera_0,camera_1};

	Camera* camera;


	// Camera* camera = new Camera();
	// camera->SetLocation(Eigen::Vector3f(0.0f,0.0f,1.0f));
	// camera->SetRotation(Eigen::Quaternionf(0.0f,0.0f,1.0f,0.0f));
	// camera->SetSize(1.0f);
	// camera->SetMoveSpeed(100.0f);

	// Camera* curr_camera = Controller::GetCurrCamera();

	Shader* shader = new Shader("brdf","C:/WorkSpace/VS/Engine/TSUBAKI/shader/brdf_base");
	
	Material* material_0 = new Material("material_01",shader);

	std::string TBKpath = "C:/WorkSpace/Asset/Model/tsubaki.tbk";
	TBKScene* scene = new TBKScene();
	Importer::LoadTBK(TBKpath,scene);

	std::vector<Mesh*> mesh_list;

	for(int i=0;i<Importer::GetMeshNumFromTBKScene(scene);i++)
	{
		mesh_list.push_back(Importer::GetMeshFromTBKScene(scene,i));
	}

	Vertex v1;
	v1.SetPosition(-10.0f,0.0f,0.0f);
	v1.SetUV(0.0f,1.0f);
	v1.SetNormal(0.0f,0.0f,1.0f);
	Vertex v2;
	v2.SetPosition(10.0f,0.0f,0.0f);
	v2.SetUV(1.0f,1.0f);
	v2.SetNormal(0.0f,0.0f,1.0f);
	Vertex v3;
	v3.SetPosition(10.0f,10.0f,0.0f);
	v3.SetUV(1.0f,0.0f);
	v3.SetNormal(0.0f,0.0f,1.0f);
	Vertex v4;
	v4.SetPosition(-10.0f,10.0f,0.0f);
	v4.SetUV(0.0f,0.0f);
	v4.SetNormal(0.0f,0.0f,1.0f);
	std::vector<Vertex> vertices({v1,v2,v3,v4});
	std::vector<unsigned int> indices({0,1,2,0,2,3});
	Mesh* quad = new Mesh("Quad",vertices,indices);

	mesh_list.push_back(quad);

	Texture* texture_1 = Importer::LoadTexture("texture_1","C:/WorkSpace/Asset/Texture/re_miku.jpg");

	DirectionalLight* dir_light_0 = new DirectionalLight();
	dir_light_0->SetLightDirection((Eigen::Vector3f(0.0f,0.0f,1.0f).normalized()));
	dir_light_0->SetLightColor(Eigen::Vector3f(1.0f,0.0f,0.0f));
	PointLight* point_light_0 = new PointLight();
	point_light_0->SetLightColor(Eigen::Vector3f(0.0f,0.0f,1.0f));
	//AmbientLight* ambient_light_0 = new AmbientLight();

	Eigen::Matrix4f identity = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f translate = identity;
	Eigen::Quaternionf rotation = Eigen::Quaternionf(0.707f,-0.707f,0.0f,0.0f);
	Eigen::Translation3f translation(0.0f,-50.0f,-500.0f);
	Eigen::AlignedScaling3f scale(10.f,10.f,10.f);
	Eigen::Affine3f transform = translation*rotation*scale;
	Eigen::Matrix4f transform_matrix = transform.matrix();


	while(curr_window->GetCurrFrameCount()<100000)
	{
		std::cout << "Frame Count : " <<curr_window->GetCurrFrameCount() << std::endl;
		std::cout << "FPS : " <<1.0f/curr_window->GetCurrDeltaTime()<<std::endl;
		curr_window->RefreshFrame(1.0f, 1.0f, 1.0f, 1.0f);
		Controller::UpdateObject(curr_window->GetCurrDeltaTime());
		camera_list[0]->SetAsCurrCamera();
		camera = Controller::GetCurrCamera();

		material_0->UseMaterial(transform_matrix);
		// shader->UseShader();
		// shader->SetUniformInt("dir_light_num",Controller::GetDirectionalLightNum());
		// for(int i=0;i<Controller::GetDirectionalLightNum();i++)
		// {
		// 	DirectionalLight* dir_light = Controller::GetDirectionalLight(i);
		// 	shader->SetUniformVec3("dir_light_array["+std::to_string(i)+"].dir",dir_light->GetLightDirection());
		// 	shader->SetUniformVec3("dir_light_array["+std::to_string(i)+"].color",dir_light->GetLightColor());
		// }
		// shader->SetUniformVec3("ambient_color",Eigen::Vector3f(0.010f,0.010f,0.010f));
		// shader->SetUniformVec3("albedo",Eigen::Vector3f(1.0f,1.0f,1.0f));
		// shader->SetUniformFloat("metallic",0.0f);
		// shader->SetUniformFloat("roughness",1.0f);
		// //shader->SetUniformFloat("ao",1.0f);
		
		// shader->SetUniformVec3("view_position",camera->GetLocation());
		// shader->SetUniformBool("use_albedo_texture",false);
		// shader->SetUniformBool("use_normal_texture",false);
		// shader->SetUniformBool("use_metallic_texture",false);
		// shader->SetUniformBool("use_roughness_texture",false);
		// //shader->SetUniformBool("use_ao_texture",false);
		// shader->SetUniformBool("use_ambient_texture",false);



		// shader->SetUniformMatrix4x4("transform_matrix",transform_matrix);
		// shader->SetUniformMatrix4x4("camera_matrix",camera->GetToLocalMatrix());
		// shader->SetUniformMatrix4x4("projection_matrix",  camera->GetProjectionMatrix());


		for(int i=0;i<mesh_list.size();i++)
		{
			mesh_list[i]->DrawMesh();
		}

		curr_window->SwapBuffer();
		////////////
	}
	curr_window->CloseWindow();

	Initializer::EndEngine();
	return 0;
}