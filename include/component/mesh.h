#ifndef __TSUBAKI_MESH__
#define __TSUBAKI_MESH__

#include <vector>
#include <string>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <utility/basic.h>
#include <component/material.h>

struct Vertex
{
    Eigen::Vector3f position;
    Eigen::Vector3f normal;
    // Eigen::Vector3f tangent;
    // Eigen::Vector3f bitangent;
    Eigen::Vector2f uv_1;
    // Eigen::Vector2f uv_2;
    void SetPosition(float x,float y,float z)
    {
        position.x() = x;
        position.y() = y;
        position.z() = z;
    }
    void SetNormal(float x,float y,float z)
    {
        normal.x() = x;
        normal.y() = y;
        normal.z() = z;
    }
    void SetUV(float x,float y)
    {
        uv_1.x() = x;
        uv_1.y() = y;
    }
};

class Mesh{
public:
    Mesh(const std::string& init_label,
    const std::vector<Vertex>& init_vertices,
    const std::vector<unsigned int>& init_indices
    );
    ~Mesh();
    std::string GetLabel() const;
    void DrawMesh() const;
private:
    void BindToHardware();
    void DrawToHardware() const;
    std::string label;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

#endif