#pragma once
#include "texture.h"
#include "vao.h"
#include "ibo.h"
#include "vbo.h"
#include "pipeline.h"

struct Vertex
{
	Vertex(glm::vec3 p = glm::vec3(0), glm::vec3 n = glm::vec3(0), 
		glm::vec2 t = glm::vec2(0)) 
		: Position(p), Normal(n), TexCoords(t)/*, index(0)*/ {}
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	//int index;
};

class Mesh
{
public:

	explicit Mesh(std::vector<Vertex> vertices, 
		std::vector<unsigned> indices, 
		std::vector<Texture> textures);
	Mesh(const Mesh& other);
	~Mesh();

	void Draw();

	const std::vector<Vertex>& GetVertices() const { return vertices; }
	const std::vector<GLuint>& GetIndices() const { return indices; }
	const std::vector<Texture>& GetTextures() const { return textures; }

	VBO* GetVBO() { return vbo; }
protected:
	Mesh() = delete;

	VAO* vao = nullptr;
	VBO* vbo = nullptr;
	IBO* ibo = nullptr;

  unsigned vertCount;
	bool indexed; // whether to use DrawElements or DrawArrays
	void setupBuffers();

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
};