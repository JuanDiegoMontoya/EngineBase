#pragma once

class VAO;
class VBO;

// rendering class
class Line
{
public:
	Line(const glm::vec3& pos, const glm::vec3& dir,
				const glm::vec3& tclr, const glm::vec3& bclr);
	~Line();

	// the user must provide a shader and correct uniforms to draw
	void Draw() const;

private:
	glm::vec3 pos_; // model space position of the line
	glm::vec3 dir_;	// direction AND length (user might want to normalize)
	glm::vec3 tclr_;// top color
	glm::vec3 bclr_;// bottom color

	// rendering
	VAO* vao_;
	VBO* positions_;
	VBO* colors_;
};

// many lines in one buffer (efficient)
// like lineinstanced, but for one object, and not instanced
class LinePool
{
public:
	LinePool(
		const std::vector<glm::vec3>& wposs, const std::vector<glm::vec3>& dirs,
		const std::vector<glm::vec3>& tclrs, const std::vector<glm::vec3>& bclrs
	);
	~LinePool()
	{
		delete vao_;
		delete positions_;
		delete colors_;
	}

	void Draw() const;

private:
	VAO* vao_;
	VBO* positions_;
	VBO* colors_;

	GLuint count_ = 0;
};