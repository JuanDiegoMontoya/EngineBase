#include "../../stdafx.h"
#include "abo.h"

ABO::ABO(GLuint num) : numCounters_(num)
{
	glGenBuffers(1, &rendererID_);
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, rendererID_);
	//glBufferData(GL_ATOMIC_COUNTER_BUFFER, numCounters_ * sizeof(GLuint), NULL, GL_STATIC_READ);
	glBufferStorage(GL_ATOMIC_COUNTER_BUFFER, numCounters_ * sizeof(GLuint), NULL,
		GL_DYNAMIC_STORAGE_BIT |
		GL_MAP_READ_BIT |
		GL_MAP_WRITE_BIT |
		GL_CLIENT_STORAGE_BIT);
}

ABO::~ABO()
{
	glDeleteBuffers(1, &rendererID_);
}

void ABO::Bind(GLuint index)
{
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, rendererID_);
	glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, index, rendererID_);
}

void ABO::Unbind()
{
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
}

void ABO::Reset()
{
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, rendererID_);
	GLuint* buffer;
	buffer = (GLuint*)glMapBufferRange(
		GL_ATOMIC_COUNTER_BUFFER,
		0,
		numCounters_ * sizeof(GLuint),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	std::memset(buffer, 0, numCounters_ * sizeof(GLuint));
	glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);
}

void ABO::Set(GLuint index, GLuint value)
{
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, rendererID_);
	// sets a single atomic's value
	glBufferSubData(
		GL_ATOMIC_COUNTER_BUFFER,
		index * sizeof(GLuint),
		sizeof(GLuint),
		&value);
}

GLuint ABO::Get(GLuint index)
{
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, rendererID_);
	// gets a single atomic's value
	GLuint val;
	glGetBufferSubData(
		GL_ATOMIC_COUNTER_BUFFER,
		index * sizeof(GLuint),
		sizeof(GLuint),
		&val);
	return val;
}
