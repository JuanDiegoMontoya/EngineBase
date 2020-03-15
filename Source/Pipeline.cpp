#include "../../stdafx.h"
#include <shader.h>
#include "Pipeline.h"

void Pipeline::SetShader(std::string shader)
{
	activeShader_ = Shader::shaders[shader];
}