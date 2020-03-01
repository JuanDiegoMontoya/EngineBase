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

	std::string vsPath;	// vertex shader path
	std::string tcsPath;// tessellation control shader path
	std::string tesPath;// tessellation evaluation shader path
	std::string gsPath;	// geometry shader path
	std::string fsPath;	// fragment shader path
	std::string csPath;	// compute shader path

	// maps strings to GPU memory addresses (as GLints)
	//std::unordered_map<const char*, GLint, Utils::djb2hash, Utils::charPtrKeyEq> Uniforms;
	std::unordered_map<std::string, GLint> Uniforms;
	//std::map<const char*, GLint> Uniforms;

	// standard vertex + fragment program constructor
	Shader(const char* vertexPath, const char* fragmentPath,
		const char* tessCtrlPath = "<null>",
		const char* tessEvalPath = "<null>",
		const char* geometryPath = "<null>");

	// default constructor (currently no uses)
	inline Shader() : shaderID(shader_count_)
	{
		//type = sDefault;
		programID = NULL;
		shader_count_++;
	}

	inline ~Shader()
	{
		glDeleteProgram(programID);
	}

	// set the active shader to this one
	inline void Use() const
	{
		glUseProgram(programID);
	}

	inline void Unuse() const
	{
		glUseProgram(0);
	}

	inline void setBool(const char* name, bool value)
	{
		glUniform1i(Uniforms[name], (int)value);
	}
	inline void setInt(const char* name, int value)
	{
		glUniform1i(Uniforms[name], value);
	}
	inline void setFloat(const char* name, float value)
	{
		glUniform1f(Uniforms[name], value);
	}
	inline void set3FloatArray(const char* name, const float* value, int count)
	{
		glUniform3fv(Uniforms[name], count, &value[0]);
	}
	inline void set4FloatArray(const char* name, const float* value, int count)
	{
		glUniform4fv(Uniforms[name], count, &value[0]);
	}
	inline void setIntArray(const char* name, std::vector<int> value)
	{
		glUniform1iv(Uniforms[name], value.size(), &value[0]);
	}
	inline void set1FloatArray(const char* name, std::vector<float>& value, int count)
	{
		glUniform1fv(Uniforms[name], count, &value[0]);
	}
	inline void set2FloatArray(const char* name, std::vector<glm::vec2>& value, int count)
	{
		glUniform2fv(Uniforms[name], count, &value[0].x);
	}
	inline void set3FloatArray(const char* name, std::vector<glm::vec3>& value, int count)
	{
		glUniform3fv(Uniforms[name], count, &value[0].x);
	}
	inline void set4FloatArray(const char* name, std::vector<glm::vec4>& value, int count)
	{
		glUniform4fv(Uniforms[name], count, &value[0].x);
	}
	inline void setVec2(const char* name, const glm::vec2 &value)
	{
		glUniform2fv(Uniforms[name], 1, &value[0]);
	}
	inline void setVec2(const char* name, float x, float y)
	{
		glUniform2f(Uniforms[name], x, y);
	}
	inline void setVec3(const char* name, const glm::vec3 &value)
	{
		glUniform3fv(Uniforms[name], 1, &value[0]);
	}
	inline void setVec3(const char* name, float x, float y, float z)
	{
		glUniform3f(Uniforms[name], x, y, z);
	}
	inline void setVec4(const char* name, const glm::vec4 &value)
	{
		glUniform4fv(Uniforms[name], 1, &value[0]);
	}
	inline void setVec4(const char* name, float x, float y, float z, float w)
	{
		glUniform4f(Uniforms[name], x, y, z, w);
	}
	inline void setMat3(const char* name, const glm::mat3 &mat)
	{
		glUniformMatrix3fv(Uniforms[name], 1, GL_FALSE, &mat[0][0]);
	}
	inline void setMat4(const char* name, const glm::mat4 &mat)
	{
		PERF_BENCHMARK_START;
		//glUniformMatrix4fv(Uniforms[name], 1, GL_FALSE, &mat[0][0]);
		glProgramUniformMatrix4fv(programID, Uniforms[name], 1, GL_FALSE, &mat[0][0]);
		PERF_BENCHMARK_END;
	}

	// (static) list of all shader programs
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
	static const char* shader_dir_;
	std::string loadShader(const char* path);
	GLint compileShader(shadertype type, const GLchar* src);
}Shader, *ShaderPtr;