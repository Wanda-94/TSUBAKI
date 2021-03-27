#include <component/shader.h>

void ShaderCompiler::checkCompileErrors(unsigned int shader, std::string type)
{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
}
unsigned int ShaderCompiler::CreateShader(const std::string label,const std::string dir_name)
{
		unsigned int id;
		std::string vertex_shader_path = dir_name + "/"+label+".vs";
		std::string fragment_shader_path = dir_name + "/"+label+".fs";
		const char* vertexPath = vertex_shader_path.c_str();
		const char* fragmentPath = fragment_shader_path.c_str();
		{
			// 1. retrieve the vertex/fragment source code from filePath
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;
			// ensure ifstream objects can throw exceptions:
			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				// open files
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				std::stringstream vShaderStream, fShaderStream;
				// read file's buffer contents into streams
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();
				// close file handlers
				vShaderFile.close();
				fShaderFile.close();
				// convert stream into string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
				// if geometry shader path is present, also load a geometry shader
			}
			catch (std::ifstream::failure& e)
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			}
			const char* vShaderCode = vertexCode.c_str();
			const char * fShaderCode = fragmentCode.c_str();
			// 2. compile shaders
			unsigned int vertex, fragment;
			// vertex shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);
			checkCompileErrors(vertex, "VERTEX");
			// fragment Shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			checkCompileErrors(fragment, "FRAGMENT");
			// if geometry shader is given, compile geometry shader

			// shader Program
			id = glCreateProgram();
			glAttachShader(id, vertex);
			glAttachShader(id, fragment);
			glLinkProgram(id);
			checkCompileErrors(id, "PROGRAM");
			// delete the shaders as they're linked into our program now and no longer necessery
			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}
		return id;
}

Shader::Shader(const std::string label,const std::string shader_path)
{
	shader_ref = ShaderCompiler::CreateShader(label,shader_path);
}

Shader::~Shader()
{
    glDeleteShader(shader_ref);
}

void Shader::UseShader()
{
	glUseProgram(shader_ref);
}

void Shader::SetUniformMatrix4x4(const std::string& name,const Eigen::Matrix4f& matrix4x4) const
{
	glUniformMatrix4fv(glGetUniformLocation(shader_ref, name.c_str()), 1, GL_FALSE, matrix4x4.data());
}

void Shader::SetUniformBool(const std::string& name,const bool value) const
{
	glUniform1i(glGetUniformLocation(shader_ref,name.c_str()),value);
}

void Shader::SetUniformFloat(const std::string& name,const float value) const
{
	glUniform1f(glGetUniformLocation(shader_ref,name.c_str()),value);
}
void Shader::SetUniformInt(const std::string& name,const int value) const 
{
	glUniform1i(glGetUniformLocation(shader_ref,name.c_str()),value);
}

void Shader::SetUniformVec3(const std::string& name,const Eigen::Vector3f& value) const
{
	glUniform3fv(glGetUniformLocation(shader_ref,name.c_str()),1,value.data());
}