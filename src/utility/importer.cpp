#include <utility/importer.h>

void ProcessNode(const aiNode* node, const aiScene* scene);

std::vector<std::string> StringSplit(const std::string& s,const char& c)
{
    std::vector<std::string> s_list;
    std::string part = "";
    bool flag = false;
    for(int i=0;i<s.length();i++)
    {
        if(flag==false)
        {
            if(s[i]==c)
            {
                continue;
            }
            else
            {
                flag = true;
                part = "";
                part+=s[i];
            }
        }
        else
        {
            if(s[i]==c)
            {
                if(part.length()!=0)
                {
                    s_list.push_back(part);
                    part = "";
                    flag = false;
                }
            }
            else
            {
                part+=s[i];
            }
        }
    }
    if(flag)
    {
        s_list.push_back(part);
    }
    return s_list;
}

void RunReadFunction(std::string& type,std::ifstream& file_stream,TBKScene* scene)
{
    bool find_relative_function = false;
    for(int i=0;i<TBK_function_num;i++)
    {
        if(type==TBK_type_s[i])
        {
            find_relative_function = true;
            TBK_read_function[i](file_stream,scene);
            break;
        }
    }
    std::cout<<type + " over"<<std::endl;
    assert(find_relative_function);
}

// void Importer::LoadModel(const std::string& path)
// {
// 	Assimp::Importer importer;
//     const aiScene* scene;
//     scene = importer.ReadFile(path,aiProcess_FlipUVs|aiProcess_Triangulate|aiProcess_CalcTangentSpace);
//     if(scene == nullptr || scene->mRootNode == nullptr)
//     {
//         std::cout<<importer.GetErrorString()<<std::endl;
//     }
//     else
//     {
//         std::cout<<" mesh num : "<<scene->mNumMeshes<<std::endl;
//         std::cout << " fuck " << std::endl;
//         ProcessNode(scene->mRootNode, scene);
//     }
// }

// void ProcessNode(const aiNode* node, const aiScene* scene)
// {
//     std::cout << " prcess node : " << node->mName.data << std::endl;
//     std::cout << "transform:" << std::endl;
//     std::cout << node->mTransformation.a1 << " " << node->mTransformation.a2 << " " << node->mTransformation.a3 << " " << node->mTransformation.a4 << std::endl;
//     std::cout << node->mTransformation.b1 << " " << node->mTransformation.b2 << " " << node->mTransformation.b3 << " " << node->mTransformation.b4 << std::endl;
//     std::cout << node->mTransformation.c1 << " " << node->mTransformation.c2 << " " << node->mTransformation.c3 << " " << node->mTransformation.c4 << std::endl;
//     std::cout << node->mTransformation.d1 << " " << node->mTransformation.d2 << " " << node->mTransformation.d3 << " " << node->mTransformation.d4 << std::endl;
//     for (int i = 0; i < node->mNumChildren; i++)
//     {
//         ProcessNode(node->mChildren[i], scene);
//     }
// }

void Importer::LoadTBK(const std::string& path,TBKScene* scene)
{
    assert(scene!=nullptr);
    std::ifstream file_stream(path.c_str(),std::ios::in);
    //file_stream.open(path.c_str(),std::ios_base::in);
    if(file_stream.is_open())
    {
        std::string line = "";
        //line = file_stream.getline(line);
        while(std::getline(file_stream,line))
        {
            if(line[0]!='#')
            {
                std::cout<<line<<std::endl;
            }
            else
            {
                if(line[0] == '#')
                {
                    TBKReadScene(file_stream,scene);
                }
            }
        }
    }
}
void Importer::TBKReadScene(std::ifstream& file_stream,TBKScene* scene)
{
    std::string line = "";
    while(std::getline(file_stream,line))
    {
        if(line == "##")
        {
            TBKReadBlock(file_stream,scene);
        }
        else if(line == "#")
        {
            break;
        }
    }
}
void Importer::TBKReadBlock(std::ifstream& file_stream,TBKScene* scene)
{
    // TBKType read_type = TBKType::TBK_NONE;
    std::string line = "";
    std::getline(file_stream,line);
    assert(line.length()!=0);
    std::vector<std::string> par(StringSplit(line,':'));
    assert(par[0]=="type");
    RunReadFunction(par[1],file_stream,scene);
}
void Importer::TBKReadArmature(std::ifstream& file_stream,TBKScene* scene)
{
    scene->tbk_flag |= (int)(TBKFlag::TBK_HAS_ARMATURE);
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    assert(par[0]=="label");
    scene->AddArmature(par[1]);
    while(std::getline(file_stream,line))
    {
        {
            if(line=="###")
            {
                std::getline(file_stream,line);
                auto par_data_type = StringSplit(line,':');
                RunReadFunction(par_data_type[1],file_stream,scene);
            }
            else if(line[0]=='#')
            {
                break;
            }
        }
    }
}
void Importer::TBKReadBone(std::ifstream& file_stream,TBKScene* scene)
{
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    TBKBone bone;
    assert(par[0]=="label");
    bone.label = par[1];
    std::getline(file_stream,line);
    bone.index = std::stoi(line);
    std::getline(file_stream,line);
    bone.parent_index = std::stoi(line);
    std::getline(file_stream,line);
    auto input_data = StringSplit(line,' ');
    assert(input_data.size()==16);
    for(int row = 0; row<4 ; row++ )
    {
        for(int column = 0;column<4;column++)
        {
            bone.bone_local_matrix.data[row][column] = std::stof(input_data[row*4+column]);
        }
    }
    scene->AddBone(bone);
    while(std::getline(file_stream,line))
    {
        if(line[0]=='#')
        {
            break;
        }
    }
}
void Importer::TBKReadMesh(std::ifstream& file_stream,TBKScene* scene)
{
    scene->tbk_flag |= (int)(TBKFlag::TBK_HAS_MESH);
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    assert(par[0]=="label");
    scene->AddMesh(par[1]);
    while(std::getline(file_stream,line))
    {
        if(line=="###")// ?
        {
                std::string type_line = "";
                std::getline(file_stream,type_line);
                auto par_data_type = StringSplit(type_line,':');
                RunReadFunction(par_data_type[1],file_stream,scene);
        }
        else
        {
            break;
        }
    }
}
void Importer::TBKReadVertex(std::ifstream& file_stream,TBKScene* scene)
{
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    assert(par[0]=="num");
    int vertex_num = std::stoi(par[1]);
    std::vector<TBKVector3f> vertices;
    while(std::getline(file_stream,line))
    {
        if(line[0]!='#')
        {
            auto input_data = StringSplit(line,' ');
            vertices.push_back(TBKVector3f(std::stof(input_data[1]),std::stof(input_data[2]),std::stof(input_data[3])));
        }
        else
        {
            break;
        }
   }
   assert(vertex_num==vertices.size());
   scene->AddVertices(vertices);
}

void Importer::TBKReadNormal(std::ifstream& file_stream,TBKScene* scene)
{
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    assert(par[0]=="num");
    int normal_num = std::stoi(par[1]);
    std::vector<TBKVector3f> normals;
    while(std::getline(file_stream,line))
    {
        if(line[0]!='#')
        {
            auto input_data = StringSplit(line,' ');
            normals.push_back(TBKVector3f(std::stof(input_data[1]),std::stof(input_data[2]),std::stof(input_data[3])));
        }
        else
        {
            break;
        }
   }
   assert(normal_num==normals.size());
   scene->AddNormals(normals);
}

void Importer::TBKReadFace(std::ifstream& file_stream,TBKScene* scene)
{
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    assert(par[0]=="num");
    int face_num = std::stoi(par[1]);
    std::vector<unsigned int> faces;
    while(std::getline(file_stream,line))
    {
        if(line[0]!='#')
        {
            auto input_data = StringSplit(line,' ');
            for(int index = 1;index<input_data.size();index++)
            {
                faces.push_back(std::stoi(input_data[index]));
            }
            //triangle or quad?
     }
        else
        {
            break;
        }
   }
   assert((face_num*3)==faces.size());
   scene->AddFaces(faces);
}

void Importer::TBKReadUV(std::ifstream& file_stream,TBKScene* scene)
{
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    assert(par[0]=="num");
    int uv_num = std::stoi(par[1]);
    std::vector<TBKVector2f> uvs;
    while(std::getline(file_stream,line))
    {
        if(line[0]!='#')
        {
            auto input_data = StringSplit(line,' ');
            uvs.push_back(TBKVector2f(std::stof(input_data[1]),std::stof(input_data[2])));
        }
        else
        {
            break;
        }
   }
   assert(uv_num==uvs.size());
   scene->AddUVs(uvs);
}
void Importer::TBKReadTangent(std::ifstream& file_stream,TBKScene* scene)
{

}
void Importer::TBKReadBitangent(std::ifstream& file_stream,TBKScene* scene)
{

}
void Importer::TBKReadAnimation(std::ifstream& file_stream,TBKScene* scene)
{
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    assert(par[0]=="label");

    std::getline(file_stream,line);
    auto input_data = StringSplit(line,':');
    int frame_num = std::stoi(input_data[1]);

    std::getline(file_stream,line);
    input_data = StringSplit(line,':');
    int bone_num = std::stoi(input_data[1]);

    std::getline(file_stream,line);
    input_data = StringSplit(line,':');
    int data_offset = std::stoi(input_data[1]);

    scene->AddAnimation(par[1],frame_num,bone_num,data_offset);
    std::vector<float> data;
    data.resize(frame_num*bone_num*data_offset);
    auto iter = data.begin();
    while(std::getline(file_stream,line))
    {
        if(line[0]=='#')
        {
            break;
        }
        else
        {
            auto input_data =  StringSplit(line,' ');
            for(int i=0;i<input_data.size();i++)
            {
                *iter = std::stof(input_data[i]);
                iter++;
            }
        }
    }
    assert(iter==data.end());
    scene->AddAnimationData(data);
}
void Importer::TBKReadWeight(std::ifstream& file_stream,TBKScene* scene)
{
    std::string line = "";
    std::getline(file_stream,line);
    auto par = StringSplit(line,':');
    assert(par[0]=="num");
    int weight_num = std::stoi(par[1]);
    std::vector<std::vector<std::pair<int,float>>> weights;
    while(std::getline(file_stream,line))
    {
        if(line[0]!='#')
        {
            auto input_data = StringSplit(line,' ');
            int p = 1;
            std::vector<std::pair<int,float>> weight;
            while(p<input_data.size()&&weight.size()<4)
            {
                weight.push_back(std::pair<int,float>(
                    std::stoi(input_data[p]),
                    std::stof(input_data[p+1])
                ));
                p+=2;
            }
            while(weight.size()<4)
            {
                weight.push_back(std::pair<int,float>(0,0.0f));
            }
            weights.push_back(weight);
        }
        else
        {
            break;
        }
    }
    assert(weights.size()==weight_num);
    scene->AddWeights(weights);
}
unsigned int Importer::GetMeshNumFromTBKScene(const TBKScene* scene)
{
    return scene->tbk_mesh_list.size();
}

Mesh* Importer::GetMeshFromTBKScene(TBKScene* scene,unsigned int index)
{
    TBKMesh* tbk_mesh = (scene->tbk_mesh_list[index]);

    std::string label = tbk_mesh->label;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for(int face_index = 0;face_index<(tbk_mesh->faces.size());face_index++)
    {
        //triangle
            Vertex vertex;
            TBKVector3f p = (tbk_mesh->vertices[tbk_mesh->faces[face_index]]);
            TBKVector3f n = (tbk_mesh->normals[tbk_mesh->faces[face_index]]);
            TBKVector2f uv = (tbk_mesh->uv_layers[0][face_index]);
            vertex.SetPosition(p.x,p.y,p.z);
            vertex.SetNormal(n.x,n.y,n.z);
            vertex.SetUV(uv.x,uv.y);
            vertices.push_back(vertex);
            indices.push_back((unsigned int)face_index);
        //
    }

    Mesh* mesh = new Mesh(label,vertices,indices);

    return mesh;
}

SkeletonMesh* Importer::GetSkeletonMeshFromTBKScene(TBKScene* scene,unsigned int index)
{
    TBKMesh* tbk_mesh = (scene->tbk_mesh_list[index]);

    std::string label = tbk_mesh->label;
    std::vector<SkeletonVertex> vertices;
    std::vector<unsigned int> indices;

    for(int face_index = 0;face_index<(tbk_mesh->faces.size());face_index++)
    {
        //triangle
            int vertex_index = tbk_mesh->faces[face_index];
            SkeletonVertex vertex;
            TBKVector3f p = (tbk_mesh->vertices[vertex_index]);
            TBKVector3f n = (tbk_mesh->normals[vertex_index]);
            TBKVector2f uv = (tbk_mesh->uv_layers[0][face_index]);
            std::vector<std::pair<int,float>> w = tbk_mesh->weights[vertex_index];
            vertex.SetPosition(p.x,p.y,p.z);
            vertex.SetNormal(n.x,n.y,n.z);
            vertex.SetUV(uv.x,uv.y);
            vertex.SetBoneIndex(w[0].first,w[1].first,w[2].first,w[3].first);
            vertex.SetBoneWeight(w[0].second,w[1].second,w[2].second,w[3].second);
            vertices.push_back(vertex);
            indices.push_back((unsigned int)face_index);
        //
    }

    SkeletonMesh* mesh = new SkeletonMesh(label,vertices,indices);

    return mesh;
}

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture* Importer::LoadTexture(const std::string& label,const std::string& path)
{
    std::cout<<"load texture form : "+path<<std::endl;

    int texture_width,texture_height,texture_channels;
    
    unsigned char* data_ptr = stbi_load(path.c_str(),&texture_width,&texture_height,&texture_channels,0);

    Texture* texture = new Texture(label,data_ptr,texture_width,texture_height,texture_channels);
    
    return texture;
}

void Importer::FreeTexture(Texture* texture)
{
    stbi_image_free(texture->GetData());
}