#include "stdafx.h"

#include "vbo.h"

VBO::VBO(const void * data, unsigned int size, GLenum drawmode)
{
		glGenBuffers(1, &rendererID_);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
		glBufferData(GL_ARRAY_BUFFER, size, data, drawmode);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &rendererID_);
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
