#pragma once

// draw indirect buffer object

struct DrawElementsIndirectCommand
{
	GLuint  count;
	GLuint  instanceCount;
	GLuint  firstIndex;
	GLuint  baseVertex;
	GLuint  baseInstance;
	// note: baseInstance is for glMultiDraw*Indirect ONLY
	// for any other purpose it must be zero
};

struct DrawArraysIndirectCommand
{
	GLuint  count;
	GLuint  instanceCount;
	GLuint  firstIndex;
	GLuint  baseInstance;
};

class DIB
{
public:
	DIB(void* data, GLsizei count, GLenum drawmode = GL_STATIC_DRAW);
	~DIB();

	void Bind() const;
	void Unbind() const;
private:
	GLuint dibID_;
};