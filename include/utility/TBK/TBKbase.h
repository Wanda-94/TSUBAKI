#ifndef __TSUBAKI_TBKBASE__
#define __TSUBAKI_TBKBASE__

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

enum class TBKType{
    TBK_NONE = 0,
    TBK_SCENE ,
    TBK_AMATURE,
    TBK_BONE,
    TBK_MESH,
    TBK_VERTEX,
    TBK_NORMAL,
    TBK_FACE,
    TBK_UV,
    TBK_TANGENT,
    TBK_BITANGENT,
    TBK_WEIGHT,
    TBK_ANIMATION,
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
    std::vector<std::vector<std::pair<int,float>>> weights;
};

// struct TBKSkeletonMesh{
//     std::string label;
//     std::vector<TBKVector3f> vertices;
//     std::vector<TBKVector3f> normals;
//     std::vector<std::vector<TBKVector2f>> uv_layers;
//     std::vector<unsigned int> faces;
//     std::vector<std::vector<std::pair<int,float>>> weights;
// };

struct TBKMaterial{

};

struct TBKMatrix4x4{
    float data[4][4] = {0.0f};
};

struct TBKBone{
    int index;
    int parent_index;
    std::string label;
    TBKMatrix4x4 bone_local_matrix;
};

struct TBKArmature{
    std::string label;
    std::vector<TBKBone> bone_list;
};

struct TBKAnimation{
    std::string label;
    int frame_num;
    int bone_num;
    int data_offset;
    std::vector<float> data;
};

enum class TBKFlag{
    TBK_HAS_ARMATURE = 1,
    TBK_HAS_BONE = 2,
    TBK_HAS_MESH = 4,
    TBK_HAS_VERTEX = 8,
    TBK_HAS_NORMAL = 16,
    TBK_HAS_UV = 32,
    TBK_HAS_TANGENT = 64,
    TBK_HAS_BITANGENT = 128,
    TBK_HAS_ANIMATION = 256,
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
    void AddBone(const TBKBone& bone);
    void AddWeights(const std::vector<std::vector<std::pair<int,float>>>& weights);
    void AddAnimation(const std::string label,int frame_num,int bone_num,int data_offset);
    void AddAnimationData(const std::vector<float>& data);

    int tbk_flag;
    std::vector<TBKMesh*> tbk_mesh_list;
    std::vector<TBKAnimation*> tbk_animation_list;
    TBKArmature* tbk_armature;
    TBKMesh* tbk_active_mesh;
    TBKAnimation* tbk_active_animation;
    
};

#endif