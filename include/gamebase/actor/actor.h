#ifndef __TSUBAKI_ACTOR__
#define __TSUBAKI_ACTOR__

#include <component/object.h>
#include <component/material.h>
#include <component/mesh.h>
#include <map>

class Actor : public Object{
public:
    Actor();
    Actor(std::string name);
    Actor( Mesh* init_mesh, MaterialBase* init_material);
    Actor(std::string name, Mesh* init_mesh, MaterialBase* init_material);
    // Mesh* GetMesh();
    // Mesh GetMeshCopy();
    // void SetMesh(const Mesh* new_mesh);
    // Material* GetMaterial();
    // Material GetMaterialCopy();
    // void SetMaterial(const Material* new_material);
    virtual ~Actor();
    virtual void Update(float delta_time); 
private:
    Mesh* mesh;
    MaterialBase* material;
};

class ActorWithAnimation : public Object{
public:
    ActorWithAnimation();
    ActorWithAnimation(std::string name);
    ActorWithAnimation(SkeletonMesh* init_skeleton_mesh,MaterialBase* init_material);
    ActorWithAnimation(std::string name,SkeletonMesh* init_skeleton_mesh,MaterialBase* init_material);
    void AddAnimation(std::string name,AnimationTexture* animation_texture);
    virtual ~ActorWithAnimation();
    virtual void Update(float delta_time);
private:
    float fps;
    float animation_start_time;
    SkeletonMesh* skeleton_mesh;
    MaterialBase* material;
    std::map<std::string,AnimationTexture*> animation_map;
};

class Square : public Object{
public:
    Square(MaterialBase* init_material);
    virtual ~Square();
    virtual void Update(float delta_time);
private:
    Mesh* mesh;
    MaterialBase* material;
};

#endif