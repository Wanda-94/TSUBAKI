#include <gamebase/actor.h>

Actor::Actor(const Mesh* init_mesh,const Material* init_material)
{
    this->mesh = init_mesh;
    this->material = init_material;
}

Actor::~Actor()
{

}

void Actor::Update(float delta_time)
{
    
}