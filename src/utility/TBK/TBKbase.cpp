#include <utility/TBK/TBKbase.h>

TBKScene::TBKScene()
{
    tbk_flag = 0;
    tbk_mesh_list.resize(0);
    tbk_animation_list.resize(0);
    tbk_armature = nullptr;
    tbk_active_mesh = nullptr;
    tbk_active_animation = nullptr;
}

TBKScene::~TBKScene()
{
    for(int i=0;i<tbk_mesh_list.size();i++)
    {
        if(tbk_mesh_list[i]!=nullptr)
        {
            delete tbk_mesh_list[i];
        }
        if(tbk_armature!=nullptr)
        {
            delete tbk_armature;
        }
    }
}

void TBKScene::AddArmature(std::string label)
{
    std::cout<<"add armature "+label<<std::endl;
    this->tbk_armature = new TBKArmature();
    assert(this->tbk_armature!=nullptr);
    this->tbk_armature->label = label;
}
void TBKScene::AddMesh(const std::string label)
{
    std::cout<<"add mesh "+label<<std::endl;
    TBKMesh* tbk_mesh_ptr = new TBKMesh();
    assert(tbk_mesh_ptr!=nullptr);
    tbk_mesh_ptr->label = label;
    this->tbk_active_mesh = tbk_mesh_ptr;
    this->tbk_mesh_list.push_back(tbk_mesh_ptr);
}
void TBKScene::AddVertices(const std::vector<TBKVector3f>& vertices)
{
    std::cout<<"add vertices num : " + std::to_string(vertices.size())<<std::endl;
    assert(this->tbk_active_mesh!=nullptr);
    this->tbk_active_mesh->vertices = std::move(vertices);
}
void TBKScene::AddNormals(const std::vector<TBKVector3f>& normals)
{
    std::cout<<"add normals num : " + std::to_string(normals.size())<<std::endl;
    assert(this->tbk_active_mesh!=nullptr);
    this->tbk_active_mesh->normals = std::move(normals);
}
void TBKScene::AddFaces(const std::vector<unsigned int>& faces)
{
    std::cout<<"add faces num : " + std::to_string(faces.size())<<std::endl;
    assert(this->tbk_active_mesh!=nullptr);
    this->tbk_active_mesh->faces = std::move(faces);
}
void TBKScene::AddUVs(const std::vector<TBKVector2f>& uvs)
{
    std::cout<<"add uvs num : " + std::to_string(uvs.size())<<std::endl;
    assert(this->tbk_active_mesh!=nullptr);
    this->tbk_active_mesh->uv_layers.push_back(std::move(uvs));
}

void TBKScene::AddBone(const TBKBone& bone)
{
    this->tbk_armature->bone_list.push_back(bone);
}

void TBKScene::AddWeights(const std::vector<std::vector<std::pair<int,float>>>& weights)
{
    assert(this->tbk_active_mesh!=nullptr);
    this->tbk_active_mesh->weights = std::move(weights);
}

void TBKScene::AddAnimation(const std::string label,int frame_num,int bone_num,int data_offset)
{
    TBKAnimation* animation = new TBKAnimation();
    //int data_offset = 12;
    animation->label = label;
    animation->frame_num = frame_num;
    animation->bone_num = bone_num;
    animation->data_offset = data_offset;
    //animation->data.resize(frame_num*bone_num*data_offset);
    this->tbk_animation_list.push_back(animation);
    this->tbk_active_animation = animation;
}

void TBKScene::AddAnimationData(const std::vector<float>& data)
{
    assert(tbk_active_animation!=nullptr);
    this->tbk_active_animation->data = std::move(data);
}