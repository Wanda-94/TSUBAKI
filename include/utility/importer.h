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
    static void LoadModel(const std::string& path);
    static void LoadTBK(const std::string& path,TBKScene* scene);
    //return tbk scene
    static void TBKReadScene(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadBlock(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadArmatureInfo(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadMesh(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadVertex(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadNormal(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadFace(std::ifstream& file_stream,TBKScene* scene);
    static void TBKReadUV(std::ifstream& file_stream,TBKScene* scene);
    //convert tbk scene to engine class
    static unsigned int GetMeshNumFromTBKScene(const TBKScene* scene);
    static Mesh* GetMeshFromTBKScene(TBKScene* scene,unsigned int index);
    //import texture
    static Texture* LoadTexture(const std::string& path);
private:
    
};

const int TBK_function_num = 7;

const TBKType TBK_type[7] = {    
    TBKType::TBK_SCENE,
    TBKType::TBK_AMATURE_INFO,
    TBKType::TBK_MESH,
    TBKType::TBK_VERTEX,
    TBKType::TBK_NORMAL,
    TBKType::TBK_FACE,
    TBKType::TBK_UV,};

const std::string TBK_type_s[7] = {
    std::string("scene"),
    std::string("armature info"),
    std::string("mesh"),
    std::string("vertex"),
    std::string("normal"),
    std::string("face"),
    std::string("uv"),
};

typedef void(*TBKReadFunction)(std::ifstream& file_stream,TBKScene* scene);
const TBKReadFunction TBK_read_function[7] = {
    Importer::TBKReadScene,
    Importer::TBKReadArmatureInfo,
    Importer::TBKReadMesh,
    Importer::TBKReadVertex,
    Importer::TBKReadNormal,
    Importer::TBKReadFace,
    Importer::TBKReadUV,
};

#endif