#include <gamebase/terrain/terrain.h>

Terrain::Terrain(int init_size,MaterialBase* init_material)
{
    this->size = init_size;
    mesh = CreateTerrainMesh(init_size);
    material = init_material;
}

Terrain::~Terrain()
{

}

Mesh* Terrain::CreateTerrainMesh(int size)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    float delta = 1.0/size;
    for(int y=0;y<=size;y++)
    {
        float ind_y = y*delta;
        float ind_v = ind_y;
        for(int x=0;x<=size;x++)
        {
            float ind_x = x*delta;
            float ind_u = ind_x;
            Vertex vertex;
            vertex.SetPosition(ind_x,ind_y,0.0f);
            vertex.SetNormal(0.0f,0.0f,1.0f);
            vertex.SetUV(ind_u,ind_v);
            vertices.push_back(vertex);
        }
    }
    for(int y = 0;y<size;y++)
    {
        int start_offset = y*(size+1);
        for(int x = 0;x<size;x++)
        {
            int ind_1,ind_2,ind_3,ind_4,ind_5,ind_6;
            ind_1 = start_offset+x;
            ind_2 = ind_1+1;
            ind_3 = ind_1+(size+1);

            ind_4 = ind_2;
            ind_5 = ind_4 +(size+1);
            ind_6 = ind_5 - 1;
            indices.push_back(ind_1);
            indices.push_back(ind_2);
            indices.push_back(ind_3);
            indices.push_back(ind_4);
            indices.push_back(ind_5);
            indices.push_back(ind_6);
        }
    }
    Mesh* mesh = new Mesh("terrain",vertices,indices);
    return mesh;
}

void Terrain::Update(float delta_time)
{
    this->material->UseMaterial(this);
    this->mesh->DrawMesh();
}