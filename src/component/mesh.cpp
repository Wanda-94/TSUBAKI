#include <component/mesh.h>

Mesh::Mesh(const std::string& init_label,
    const std::vector<Vertex>& init_vertices,
    const std::vector<unsigned int>& init_indices
    )
{
    this->label = init_label;
    this->vertices = init_vertices;
    this->indices = init_indices;

    BindToHardware();
}
Mesh::~Mesh()
{
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

void Mesh::DrawMesh() const
{
    DrawToHardware();
}
void Mesh::BindToHardware()
{
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices.size(),&(vertices[0]),GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(offsetof(Vertex,position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(offsetof(Vertex,normal)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(offsetof(Vertex,uv_1)));
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&(indices[0]),GL_STATIC_DRAW);
    glBindVertexArray(0);
}
void Mesh::DrawToHardware() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    //std::cout<<"draw mesh : "<<this->label<<std::endl;
}