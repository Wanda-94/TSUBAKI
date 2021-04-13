#ifndef __TSUBAKI_TERRAIN__
#define __TSUBAKI_TERRAIN__

#include <gamebase/actor/actor.h>

class Terrain : public Object{
public:
    Terrain(int init_size,MaterialBase* init_material);
    ~Terrain();
    virtual void Update(float delta_time) override;
private:
    Mesh* CreateTerrainMesh(int size);
    int size;
    Mesh* mesh;
    MaterialBase* material;
};


#endif