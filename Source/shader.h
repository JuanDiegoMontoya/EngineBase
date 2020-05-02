#pragma once
//#include "stdafx.h"
#include "utilities.h"
#include <map>

// encapsulates shaders by storing uniforms and its GPU memory location
// also stores the program's name and both shader paths for recompiling
typedef class Shader
{
public:
	GLuint programID;		// the program's address in GPU memory
	const int shaderID;	// index into shader array
	std::string name;		// probably actual index into shader array
	std::unordered_map<std::string, GLint> Uniforms;

	std::string vsPath;	// vertex shader path
	std::string tcsPath;// tessellation control shader path
	std::string tesPath;// tessellation evaluation shader path
	std::string gsPath;	// geometry shader path
	std::string fsPath;	// fragment shader path
	std::string csPath;	// compute shader path

	// standard vertex + fragment program constructor
	Shader(const char* vertexPath, const char* fragmentPath,
		const char* tessCtrlPath = "<null>",
		const char* tessEvalPath = "<null>",
		const char* geometryPath = "<null>");

	// default constructor (currently no uses)
	Shader() : shaderID(shader_count_)
	{
		//type = sDefault;
		programID = NULL;
		shader_count_++;
	}

	~Shader()
	{
		glDeleteProgram(programID);
	}

	// set the active shader to this one
	void Use() const
	{
		glUseProgram(programID);
	}

	void Unuse() const
	{
		glUseProgram(0);
	}

	void setBool(const char* name, bool value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform1i(programID, Uniforms[name], (int)value);
	}
	void setInt(const char* name, int value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform1i(programID, Uniforms[name], value);
	}
	void setFloat(const char* name, float value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform1f(programID, Uniforms[name], value);
	}
	void set1FloatArray(const char* name, const std::vector<float>& value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform1fv(programID, Uniforms[name], value.size(), &value[0]);
	}
	void set2FloatArray(const char* name, const std::vector<glm::vec2>& value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform2fv(programID, Uniforms[name], value.size(), &value[0].x);
	}
	void set3FloatArray(const char* name, const std::vector<glm::vec3>& value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform3fv(programID, Uniforms[name], value.size(), &value[0].x);
	}
	void set4FloatArray(const char* name, const std::vector<glm::vec4>& value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform4fv(programID, Uniforms[name], value.size(), &value[0].x);
	}
	void setIntArray(const char* name, const std::vector<int>& value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform1iv(programID, Uniforms[name], value.size(), &value[0]);
	}
	void setVec2(const char* name, const glm::vec2 &value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform2fv(programID, Uniforms[name], 1, &value[0]);
	}
	void setVec2(const char* name, float x, float y)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform2f(programID, Uniforms[name], x, y);
	}
	void setVec3(const char* name, const glm::vec3 &value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform3fv(programID, Uniforms[name], 1, &value[0]);
	}
	void setVec3(const char* name, float x, float y, float z)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform3f(programID, Uniforms[name], x, y, z);
	}
	void setVec4(const char* name, const glm::vec4 &value)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform4fv(programID, Uniforms[name], 1, &value[0]);
	}
	void setVec4(const char* name, float x, float y, float z, float w)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniform4f(programID, Uniforms[name], x, y, z, w);
	}
	void setMat3(const char* name, const glm::mat3 &mat)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniformMatrix3fv(programID, Uniforms[name], 1, GL_FALSE, &mat[0][0]);
	}
	void setMat4(const char* name, const glm::mat4 &mat)
	{
		ASSERT(Uniforms.find(name) != Uniforms.end());
		glProgramUniformMatrix4fv(programID, Uniforms[name], 1, GL_FALSE, &mat[0][0]);
	}

	// list of all shader programs
	static std::unordered_map<std::string, Shader*> shaders;
private:
	enum shadertype : GLint
	{
		TY_VERTEX = GL_VERTEX_SHADER,
		TY_TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TY_TESS_EVAL = GL_TESS_EVALUATION_SHADER,
		TY_GEOMETRY = GL_GEOMETRY_SHADER,
		TY_FRAGMENT = GL_FRAGMENT_SHADER,
		TY_COMPUTE = GL_COMPUTE_SHADER
	};

	static int shader_count_;
	static constexpr const char* shader_dir_ = "./resources/Shaders/";
	std::string loadShader(const char* path);
	GLint compileShader(shadertype type, const GLchar* src);
}Shader, *ShaderPtr;