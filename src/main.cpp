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
#include <gamebase/actor/actor.h>
#include <gamebase/terrain/terrain.h>

int main(int argc,char** argv)
{

	Initializer::InitEngine();
	
	Window* curr_window = Window::GetWindowInstance();
	curr_window->SetAsCurrentWindow();
	curr_window->SetDepthTest(true);

	Camera* camera_0 = new Camera("camera_01");
	camera_0->SetLocation(Eigen::Vector3f(0.0f,0.0f,100.0f));
	camera_0->SetRotation(Eigen::Quaternionf(0.0f,0.0f,1.0f,0.0f));
	camera_0->SetMoveSpeed(100.0f);
	camera_0->SetAsCurrCamera();

	DirectionalLight* dir_light_0 = new DirectionalLight("dir_light_01");
	dir_light_0->SetLightDirection((Eigen::Vector3f(1.0f,-1.0f,-1.0f).normalized()));
	dir_light_0->SetLightColor(Eigen::Vector3f(1.0f,1.0f,1.0f));
	dir_light_0->SetIsDrawGUI(true);
	PointLight* point_light_0 = new PointLight("point_light_01");
	point_light_0->SetLightColor(Eigen::Vector3f(1.0f,1.0f,1.0f));
	point_light_0->SetAttenuation(1.0f);
	point_light_0->SetLocation(Eigen::Vector3f(0.0f,0.0f,1.0f));
	point_light_0->SetIsDrawGUI(true);
	AmbientLight* ambient_light = new AmbientLight("ambient_light_01");
	ambient_light->SetLightColor(Eigen::Vector3f(0.1f,0.1f,0.1f));
	ambient_light->SetIsDrawGUI(true);


	/////////////Miku////////////////////////////////
	// Shader* shader_0 = new Shader("brdf","C:/WorkSpace/VS/Engine/TSUBAKI/shader/brdf_base");
	

	// Material* material_0 = new Material("material_0", shader_0);
	// Material* material_1 = new Material("material_1", shader_0);
	// Material* material_2 = new Material("material_2", shader_0);
	// Material* material_3 = new Material("material_3", shader_0);
	// Material* material_4 = new Material("material_4", shader_0);
	// Material* material_5 = new Material("material_5", shader_0);
	// Material* material_6 = new Material("material_6", shader_0);
	// Material* material_7 = new Material("material_7", shader_0);

	// Texture* texture_0 = Importer::LoadTexture("texture_0","C:/WorkSpace/Asset/Texture/miku/body.png");
	// material_0->AddTexture(TextureType::TEXTURE_ALBEDO,texture_0);
	// Texture* texture_1 = Importer::LoadTexture("texture_1","C:/WorkSpace/Asset/Texture/miku/cloth_01.png");
	// material_1->AddTexture(TextureType::TEXTURE_ALBEDO,texture_1);
	// Texture* texture_2 = Importer::LoadTexture("texture_0","C:/WorkSpace/Asset/Texture/miku/cloth_02.png");
	// material_2->AddTexture(TextureType::TEXTURE_ALBEDO,texture_2);
	// Texture* texture_3 = Importer::LoadTexture("texture_3","C:/WorkSpace/Asset/Texture/miku/cloth_03.png");
	// material_3->AddTexture(TextureType::TEXTURE_ALBEDO,texture_3);
	// Texture* texture_4 = Importer::LoadTexture("texture_4","C:/WorkSpace/Asset/Texture/miku/cloth_04.png");
	// material_4->AddTexture(TextureType::TEXTURE_ALBEDO,texture_4);
	// Texture* texture_5 = Importer::LoadTexture("texture_5","C:/WorkSpace/Asset/Texture/miku/face.png");
	// material_5->AddTexture(TextureType::TEXTURE_ALBEDO,texture_5);
	// Texture* texture_6 = Importer::LoadTexture("texture_6","C:/WorkSpace/Asset/Texture/miku/hair.png");
	// material_6->AddTexture(TextureType::TEXTURE_ALBEDO,texture_6);
	// Texture* texture_7 = Importer::LoadTexture("texture_7","C:/WorkSpace/Asset/Texture/miku/pants.png");
	// material_7->AddTexture(TextureType::TEXTURE_ALBEDO,texture_7);

	// std::unordered_map<std::string,Material*> mm_map;
	// mm_map["o_body"] = material_0;
	// mm_map["o_bra"] = material_1;
	// mm_map["o_dress_01"] = material_3;
	// mm_map["o_dress_02"] = material_1;
	// mm_map["o_dress_03"] = material_1;
	// mm_map["o_dress_04"] = material_1;
	// mm_map["o_dress_05"] = material_1;
	// mm_map["o_dress_06"] = material_1;
	// mm_map["o_dress_07"] = material_3;

	// mm_map["o_face_01"] = material_5;
	// mm_map["o_footwear"] = material_3;
	// mm_map["o_hair_01"] = material_6;
	// mm_map["o_headwear_01"] = material_4;
	// mm_map["o_headwear_02"] = material_4;
	// mm_map["o_mask_01"] = material_1;
	// mm_map["o_outfit_01"] = material_1;
	// mm_map["o_outfit_02"] = material_3;
	// mm_map["o_outfit_03"] = material_3;

	// mm_map["o_pants_01"] = material_7;


	Eigen::Matrix4f identity = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f translate = identity;
	Eigen::Quaternionf rotation = Eigen::Quaternionf(0.707f,-0.707f,0.0f,0.0f);
	Eigen::Translation3f translation(0.0f,-50.0f,-500.0f);
	Eigen::AlignedScaling3f scale(10.f,10.f,10.f);
	Eigen::Affine3f transform = translation*rotation*scale;
	Eigen::Matrix4f transform_matrix = transform.matrix();

	// std::string TBKpath = "C:/BlenderOutput/Tsubaki/tsubaki.tbk";
	// TBKScene* scene = new TBKScene();
	// Importer::LoadTBK(TBKpath,scene);

	// Actor* miku = new Actor("miku");
	// // std::vector<Actor*> actor_list;
	// for(int i=0;i<Importer::GetMeshNumFromTBKScene(scene);i++)
	// {
	// 	Mesh* mesh = Importer::GetMeshFromTBKScene(scene,i);
	// 	Actor* actor = new Actor(mesh,mm_map[mesh->GetLabel()]);
	// 	miku->AddChild(actor);
	// 	// actor->SetTransformMatrix(transform_matrix);
	// 	// actor_list.push_back(actor);
	// }

	// miku->SetTransformMatrix(transform_matrix);
	/////////////Miku////////////////////////////////

	Shader* shader_0 = new Shader("brdf","C:/WorkSpace/VS/Engine/TSUBAKI/shader/brdf");
	Material* material_0 = new Material("material_0", shader_0);
	std::string TBKpath = "C:/BlenderOutput/Tsubaki/miku_for_game.tbk";
	TBKScene* scene = new TBKScene();
	Importer::LoadTBK(TBKpath,scene);

	Actor* miku = new Actor("miku");

	for(int i=0;i<Importer::GetMeshNumFromTBKScene(scene);i++)
	{
		Mesh* mesh = Importer::GetMeshFromTBKScene(scene,i);
		Actor* actor = new Actor(mesh,material_0);
		miku->AddChild(actor);
	}

	miku->SetTransformMatrix(transform_matrix);

	/////////////square//////////////////////////////
	//Material* material_square = new Material("material_square",shader_0);
	// Texture* texture_8 = Importer::LoadTexture("texture_0","C:/WorkSpace/Asset/Texture/miku.jpg");
	//material_square->AddTexture(TextureType::TEXTURE_ALBEDO,texture_8);
	//Square* square_0 = new Square(material_square);
	//square_0->SetScale(Eigen::Vector3f(10.0f,20.0f,10.0f));
	/////////////square//////////////////////////////
	// int terrain_lod = 2048;
	// float terrain_size = 300.0f*100.0f;
	// float terrain_z_scale = 100.0f;
	///////////////terrain/////////////////////////////
	//Shader* shader_1 = new Shader("terrain","C:/WorkSpace/VS/Engine/TSUBAKI/shader/terrain");
	//TerrainMaterial* material_terrain = new TerrainMaterial("material_terrain",shader_1);
	//Texture* texture_9 = Importer::LoadTexture("texture_0","C:/WorkSpace/Asset/Texture/DEM/part_14.jpg");
	//Texture* texture_10 = Importer::LoadTexture("texture_0","C:/WorkSpace/Asset/Texture/DEM/part_normal_14.jpg");
	//material_terrain->SetDEMData(texture_9,texture_10);
	//material_terrain->SetZScale(terrain_z_scale);
	//Terrain* terrain = new Terrain(terrain_lod,material_terrain);
	//terrain->SetScale(Eigen::Vector3f(terrain_size,terrain_size,1.0f));
	//terrain->SetRotation(Eigen::Quaternionf(0.707f,-0.707f,0.0f,0.0f));
	///////////////terrain/////////////////////////////

	while(curr_window->GetCurrFrameCount()<100000)
	{
		//transform_matrix(0,3)+=1.0f;
		miku->SetTransformMatrix(transform_matrix);
		std::cout << "Frame Count : " <<curr_window->GetCurrFrameCount() << std::endl;
		std::cout << "FPS : " <<1.0f/curr_window->GetCurrDeltaTime()<<std::endl;
		curr_window->DealInputEvent();
		curr_window->RefreshGUIFrame();
		Controller::DrawObjectGUI();
		curr_window->RefreshFrame();
		Controller::UpdateObject(curr_window->GetCurrDeltaTime());
		curr_window->SwapBuffer();
	}
	curr_window->CloseWindow();

	Initializer::EndEngine();
	return 0;
}