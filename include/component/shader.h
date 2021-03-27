#ifndef __TSUBAKI_SHADER__
#define __TSUBAKI_SHADER__

#include <utility/basic.h>
#include <string>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <fstream>

class ShaderCompiler{

public:
	static unsigned int CreateShader(const std::string label,const std::string dir_name);
private:
	static void checkCompileErrors(unsigned int shader, std::string type);
};

class Shader{
public:
    Shader(const std::string label,const std::string shader_path);
    ~Shader();
    void UseShader();
    void SetUniformMatrix4x4(const std::string& name,const Eigen::Matrix4f& matrix4x4) const;
    // void SetUniformVector4(const Eigen::Vector4f& vector4);
    // void SetUniformVector3(const Eigen::Vector3f& vector3);
    // void SetUniformVector2(const Eigen::Vector2f& vector2);
    // void SetUniformFloat(const float f);
    // void SetUniformBool(const bool b);
    // void SetUniformInt(const int i);
    void SetUniformBool(const std::string& name,const bool value) const;
    void SetUniformFloat(const std::string& name,const float value) const;
    void SetUniformInt(const std::string& name,const int value) const;
    void SetUniformVec3(const std::string& name,const Eigen::Vector3f& value) const;
    ////////////////////////////////////
private:
    std::string label;
    unsigned int shader_ref;
};

#endif