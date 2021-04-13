#include <gamebase/actor/actor.h>
Actor::Actor()
{
	this->mesh = nullptr;
	this->material = nullptr;
}
Actor::Actor(std::string name):Object(name)
{
	this->mesh = nullptr;
	this->material = nullptr;
}
Actor::Actor(Mesh* init_mesh,MaterialBase* init_material)
{
    this->mesh = init_mesh;
    this->material = init_material;
}
Actor::Actor(std::string name,Mesh* init_mesh,MaterialBase* init_material):Object(name)
{
    this->mesh = init_mesh;
    this->material = init_material;
}
Actor::~Actor()
{

}

void Actor::Update(float delta_time)
{
	if(this->mesh!=nullptr&&this->material!=nullptr)
	{
    	this->material->UseMaterial(this);
    	this->mesh->DrawMesh();
	}
}

Square::Square(MaterialBase* material)
{
    this->material = material;
    Vertex v1;
	v1.SetPosition(-1.0f,0.0f,0.0f);
	v1.SetUV(0.0f,0.0f);
	v1.SetNormal(0.0f,0.0f,1.0f);
	Vertex v2;
	v2.SetPosition(1.0f,0.0f,0.0f);
	v2.SetUV(1.0f,0.0f);
	v2.SetNormal(0.0f,0.0f,1.0f);
	Vertex v3;
	v3.SetPosition(1.0f,2.0f,0.0f);
	v3.SetUV(1.0f,1.0f);
	v3.SetNormal(0.0f,0.0f,1.0f);
	Vertex v4;
	v4.SetPosition(-1.0f,2.0f,0.0f);
	v4.SetUV(0.0f,1.0f);
	v4.SetNormal(0.0f,0.0f,1.0f);
	std::vector<Vertex> vertices({v1,v2,v3,v4});
	std::vector<unsigned int> indices({0,1,2,0,2,3});
	Mesh* square = new Mesh("Quad",vertices,indices);
    this->mesh = square;
}

Square::~Square()
{
    delete this->mesh;
}

void Square::Update(float delta_time)
{
    this->material->UseMaterial(this);
    this->mesh->DrawMesh();
}