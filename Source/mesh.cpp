#include "stdafx.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"

using namespace std;


Mesh::Mesh(vector<Vertex> vertices, vector<unsigned> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

  if (indices.size() > 0)
  {
    indexed = true;
    vertCount = indices.size();
  }
  else
  {
    indexed = false;
    vertCount = vertices.size();
  }

	setupBuffers();
}


// copy constructor that changes the texture mapping type
Mesh::Mesh(const Mesh& other)
{
	this->vertices = other.vertices;
	this->indices = other.indices;
	this->textures = other.textures;

	if (indices.size() > 0)
	{
		indexed = true;
		vertCount = indices.size();
	}
	else
	{
		indexed = false;
		vertCount = vertices.size();
	}

	setupBuffers();
}


Mesh::~Mesh()
{
	if (vao)
		delete vao;
	if (vbo)
		delete vbo;
	if (ibo)
		delete ibo;
}


void Mesh::Draw()
{
  vao->Bind();
  if (indexed)
    glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
  vao->Unbind();
}


void Mesh::setupBuffers()
{
	vao = new VAO();
	vbo = new VBO(&vertices[0], vertices.size() * sizeof(Vertex));

  // pos-normal-tex layout
	VBOlayout layout;
	layout.Push<GLfloat>(3);
	layout.Push<GLfloat>(3);
	layout.Push<GLfloat>(2);
	//layout.Push<GLfloat>(1);
	vao->AddBuffer(*vbo, layout);
  
	vbo->Unbind();
  if (indexed)
	  ibo = new IBO((GLuint*)&indices[0], vertCount);
	vao->Unbind();
}
