#include "../../stdafx.h"
#include "shader.h"
#include <sstream>
#include <fstream>

#include <shaderc/shaderc.hpp>

int Shader::shader_count_ = 0;

class IncludeHandler : public shaderc::CompileOptions::IncluderInterface
{
public:
	virtual shaderc_include_result* GetInclude(
		const char* requested_source,
		shaderc_include_type type,
		const char* requesting_source,
		size_t include_depth)
	{
		auto* data = new shaderc_include_result;
		
		//data->

		return data;
	}

	virtual void ReleaseInclude(shaderc_include_result* data)
	{
		// hopefully this isn't dumb
		delete[] data->content;
		delete[] data->source_name;
		delete data;
	}

private:
};

std::unordered_map<std::string, Shader*> Shader::shaders = std::unordered_map<std::string, Shader*>();

// the provided path does not need to include the shader directory
Shader::Shader(std::string vertexPath,
               std::string fragmentPath,
               std::string tessCtrlPath,
               std::string tessEvalPath,
               std::string geometryPath) 
	: shaderID(shader_count_++)
{
	//shaderc::Compiler compiler;
	//shaderc::CompileOptions options;
	//options.SetSourceLanguage(shaderc_source_language_glsl);
	//options.SetTargetEnvironment(shaderc_target_env_opengl, 460);
	//shaderc_compile_options_set_include_callbacks

	vsPath = vertexPath;
	fsPath = fragmentPath;
	tcsPath = tessCtrlPath;
	tesPath = tessEvalPath;
	gsPath = geometryPath;

	// vert/frag required
	const std::string vertRawSrc = loadFile(vertexPath);
	const std::string fragRawSrc = loadFile(fragmentPath);

	//auto vres = compiler.PreprocessGlsl(vertRawSrc, shaderc_vertex_shader, vertexPath.c_str(), options);
	//vres.

	auto [vertSrc, vertMap] = preprocessShaderSource(vertRawSrc, vertexPath);
	auto [fragSrc, fragMap] = preprocessShaderSource(fragRawSrc, fragmentPath);

	// compile individual shaders
	programID = glCreateProgram();
	GLint vShader = compileShader(TY_VERTEX, vertSrc, vertMap);
	GLint fShader = compileShader(TY_FRAGMENT, fragSrc, fragMap);
	GLint tcShader = 0;
	GLint teShader = 0;
	GLint gShader  = 0;

	//if (tessCtrlPath != "<null>")
	//{
	//	auto tscRawSrc = loadFile(tessCtrlPath);
	//	auto [tscSrc, tscMap] = preprocessShaderSource(tscRawSrc, tessCtrlPath);
	//	tcShader = compileShader(TY_TESS_CONTROL, );
	//	glAttachShader(programID, tcShader);
	//}
	//if (tessEvalPath != "<null>")
	//{
	//	teShader = compileShader(TY_TESS_EVAL, loadFile(tessEvalPath).c_str());
	//	glAttachShader(programID, teShader);
	//}
	//if (geometryPath != "<null>")
	//{
	//	gShader = compileShader(TY_GEOMETRY, loadFile(geometryPath).c_str());
	//	glAttachShader(programID, gShader);
	//}

	// vertex and fragment shaders are required (technically not frag but we want it to be here)
	glAttachShader(programID, vShader);
	glAttachShader(programID, fShader);
	glLinkProgram(programID);

	checkLinkStatus({ vertexPath, fragmentPath });

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	if (tessCtrlPath != "<null>")
		glDeleteShader(tcShader);
	if (tessEvalPath != "<null>")
		glDeleteShader(teShader);
	if (geometryPath != "<null>")
		glDeleteShader(gShader);

	initUniforms();
}

Shader::Shader(std::string computePath) : shaderID(shader_count_++)
{
	csPath = computePath;
	programID = glCreateProgram();
	const std::string compRawSrc = loadFile(computePath);
	auto [compSrc, compMap] = preprocessShaderSource(compRawSrc, computePath);
	GLint cShader = compileShader(TY_COMPUTE, compSrc, compMap);
	glAttachShader(programID, cShader);
	glLinkProgram(programID);
	checkLinkStatus({ computePath });
	glDeleteShader(cShader);

	initUniforms();
}

// loads a shader source into a string (string_view doesn't support concatenation)
std::string Shader::loadFile(std::string path)
{
	std::string shaderpath = shader_dir_ + path;
	std::string content;
	try
	{
		std::ifstream ifs(shaderpath);
		content = std::string((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error reading shader: " << path << '\n';
		std::cout << "Message: " << e.what() << std::endl;
	}
	return content;
}

// compiles a shader source and returns its ID
GLint Shader::compileShader(shadertype type, 
	const std::vector<std::string>& src, 
	const std::map<int, std::string>& strIDmap)
{
	GLuint shader = 0;
	GLchar infoLog[512];
	std::string path;
	GLint success;
	
	switch (type)
	{
	case Shader::TY_VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);
		path = vsPath;
		break;
	case Shader::TY_TESS_CONTROL:
		shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		path = tcsPath;
		break;
	case Shader::TY_TESS_EVAL:
		shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		path = vsPath;
		break;
	case Shader::TY_GEOMETRY:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		path = vsPath;
		break;
	case Shader::TY_FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		path = fsPath;
		break;
	case Shader::TY_COMPUTE:
		shader = glCreateShader(GL_COMPUTE_SHADER);
		path = csPath;
		break;
	default:
		break;
	}

	const GLchar** strings = new const GLchar*[src.size()];
	for (int i = 0; i < src.size(); i++)
		strings[i] = src[i].data();

	glShaderSource(shader, src.size(), strings, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		// TODO: parse info log to determine files in which errors ocurred

		std::cout << "File: " << path << std::endl;
		std::cout << "Error compiling shader of type " << type << '\n' << infoLog << std::endl;
	}
	else
	{
		// compile successful
	}

	return shader;
}

// TODO: https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions#ideal-way-of-retrieving-all-uniform-names
void Shader::initUniforms()
{
	// init uniform map used in that shader
	GLint max_length;
	GLint num_uniforms;

	glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
	auto pname = std::make_unique<GLchar>(max_length);
	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &num_uniforms);

	for (GLint i = 0; i < num_uniforms; ++i)
	{
		GLsizei written;
		GLint size;
		GLenum type;

		glGetActiveUniform(programID, i, max_length, &written, &size, &type, pname.get());
		GLchar* pname1 = new GLchar[max_length];
		std::strcpy(pname1, pname.get());
		if (size > 1)
			pname1[written - 3] = '\0';
		GLint loc = glGetUniformLocation(programID, pname1);
		Uniforms.insert({ pname1, loc });
		//delete pname1;
	}
}

void Shader::checkLinkStatus(std::vector<std::string_view> files)
{
	// link program
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "File(s): ";// << vertexPath << ", " << fragmentPath << '\n';
		for (const auto& file : files)
			std::cout << file << (file == *(files.end() - 1) ? "" : ", "); // no comma on last element
		std::cout << '\n';
		std::cout << "Failed to link shader program\n" << infoLog << std::endl;
		//traceMessage(std::string(infoLog));
	}
	else
	{
		// link successful
	}
}


std::tuple<std::vector<std::string>, std::map<int, std::string>>
Shader::preprocessShaderSource(std::string_view src, std::string_view filename)
{
	return { { std::string(src) }, std::map<int, std::string>() };
}
