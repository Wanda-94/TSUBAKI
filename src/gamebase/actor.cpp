#include <gamebase/actor.h>

Actor::Actor(Mesh* init_mesh,Material* init_material)
{
    this->mesh = init_mesh;
    this->material = init_material;
}

Actor::~Actor()
{

}

void Actor::Update(float delta_time)
{
    this->material->UseMaterial(GetTransformMatrix());
    this->mesh->DrawMesh();
}