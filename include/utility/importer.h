#ifndef __TSUBAKI_IMPORTER__
#define __TSUBAKI_IMPORTER__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <utility/TBK/TBKbase.h>
#include <assimp/importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <component/mesh.h>
#include <component/texture.h>
//v n 


class Importer{
public:
    //static void LoadModel(const std::string& path);
    static void LoadTBK(const std::string& path,TBKScene* scene);
    //return tbk scene
    static void TBKReadScene(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadBlock(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadArmature(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadBone(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadMesh(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadVertex(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadNormal(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadFace(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadUV(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadTangent(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadBitangent(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadWeight(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadAnimation(std::ifstream& file_stream,TBKScene* scene);
    //convert tbk scene to engine class
    static unsigned int GetMeshNumFromTBKScene(const TBKScene* scene);
    static Mesh* GetMeshFromTBKScene(TBKScene* scene,unsigned int index);
    //import texture
    static Texture* LoadTexture(const std::string& label,const std::string& path);
    static void FreeTexture(Texture* texture);
private:
    
};

const int TBK_function_num = 12;

const TBKType TBK_type[12] = {    
    TBKType::TBK_SCENE,
    TBKType::TBK_AMATURE,
    TBKType::TBK_BONE,
    TBKType::TBK_MESH,
    TBKType::TBK_VERTEX,
    TBKType::TBK_NORMAL,
    TBKType::TBK_FACE,
    TBKType::TBK_UV,
    TBKType::TBK_TANGENT,
    TBKType::TBK_BITANGENT,
    TBKType::TBK_WEIGHT,
    TBKType::TBK_ANIMATION,
};

const std::string TBK_type_s[12] = {
    std::string("scene"),
    std::string("armature"),
    std::string("bone"),
    std::string("mesh"),
    std::string("vertex"),
    std::string("normal"),
    std::string("face"),
    std::string("uv"),
    std::string("tangent"),
    std::string("bitangent"),
    std::string("weight"),
    std::string("animation"),
};

typedef void(*TBKReadFunction)(std::ifstream& file_stream,TBKScene* scene);
const TBKReadFunction TBK_read_function[12] = {
    Importer::TBKReadScene,
    Importer::TBKReadArmature,
    Importer::TBKReadBone,
    Importer::TBKReadMesh,
    Importer::TBKReadVertex,
    Importer::TBKReadNormal,
    Importer::TBKReadFace,
    Importer::TBKReadUV,
    Importer::TBKReadTangent,
    Importer::TBKReadBitangent,
    Importer::TBKReadWeight,
    Importer::TBKReadAnimation,
};

#endif