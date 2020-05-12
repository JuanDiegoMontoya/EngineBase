#include "../../stdafx.h"
#include "dib.h"

DIB::DIB(DrawElementsIndirectCommand* data, GLsizei num, GLenum drawmode)
{
	glGenBuffers(1, &dibID_);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, dibID_);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsIndirectCommand) * num, data, drawmode);
}

DIB::~DIB()
{
	glDeleteBuffers(1, &dibID_);
}

void DIB::Bind() const
{
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, dibID_);
}

void DIB::Unbind() const
{
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
}