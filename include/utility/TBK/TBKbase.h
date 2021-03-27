#ifndef __TSUBAKI_TBKBASE__
#define __TSUBAKI_TBKBASE__

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

enum class TBKType{
    TBK_NONE = 0,
    TBK_SCENE ,
    TBK_AMATURE_INFO,
    TBK_MESH,
    TBK_VERTEX,
    TBK_NORMAL,
    TBK_FACE,
    TBK_UV,
};

enum class TBKFaceType{
    TBK_FACE_TRIANGLE,
    TBK_FACE_QUAD,
};

struct TBKVector2f{
    float x;
    float y;
    TBKVector2f(){x = 0.0f; y = 0.0f;}
    TBKVector2f(float ix,float iy):x(ix),y(iy){}
};

struct TBKVector3f{
    float x;
    float y;
    float z;
    TBKVector3f(){x = 0.0f; y = 0.0f; z = 0.0f;}
    TBKVector3f(float ix,float iy,float iz):x(ix),y(iy),z(iz){}
};

struct TBKMesh{
    std::string label;
    std::vector<TBKVector3f> vertices;
    std::vector<TBKVector3f> normals;
    std::vector<std::vector<TBKVector2f>> uv_layers;
    std::vector<unsigned int> faces;
};

struct TBKMaterial{

};

struct TBKArmature{
    std::string label;
};

class TBKScene{
public:
    TBKScene();
    virtual ~TBKScene();
    TBKScene(const TBKScene& s) = delete;
    TBKScene operator=(const TBKScene& s) = delete;
    void AddArmature(const std::string label);
    void AddMesh(const std::string label);
    void AddVertices(const std::vector<TBKVector3f>& vertices);
    void AddNormals(const std::vector<TBKVector3f>& normals);
    void AddFaces(const std::vector<unsigned int>& faces);
    void AddUVs(const std::vector<TBKVector2f>& uvs);

    std::vector<TBKMesh*> tbk_mesh_list;
    TBKArmature* tbk_armature;
    TBKMesh* tbk_active_mesh;
    
};


#endif