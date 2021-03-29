#ifndef __TSUBAKI_ACTOR__
#define __TSUBAKI_ACTOR__

#include <component/object.h>
#include <component/material.h>
#include <component/mesh.h>

class Actor : public Object{
public:

    Actor( Mesh* init_mesh, Material* init_material);

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
    Material* material;
};

#endif