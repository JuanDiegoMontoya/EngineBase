#include "../../stdafx.h"
#include "Line.h"
#include "vao.h"
#include "vbo.h"
#include "shader.h"
#include "camera.h"
#include "pipeline.h"


Line::Line(const glm::vec3 & wpos, const glm::vec3 & dir,
						const glm::vec3 & tclr, const glm::vec3 & bclr)
	: pos_(wpos), dir_(dir), tclr_(tclr), bclr_(bclr)
{
	glm::vec3 pdata[2]; // start/end pos
	glm::vec3 cdata[2]; // start/end color

	pdata[0] = pos_;
	pdata[1] = pos_ + dir_;
	cdata[0] = bclr;
	cdata[1] = tclr;

	vao_ = new VAO();
	positions_ = new VBO(pdata, sizeof(pdata), GL_STATIC_DRAW);
	colors_ = new VBO(cdata, sizeof(cdata), GL_STATIC_DRAW);

	// do raw GL calls since AddBuffer() doesn't work with multiple buffers
	positions_->Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	colors_->Bind();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
}

Line::~Line()
{
	delete vao_;
	delete positions_;
	delete colors_;
}

void Line::Draw() const
{
	vao_->Bind();
	glDrawArrays(GL_LINES, 0, 2);
}


//################################# Line Pool Stuff ###############################

LinePool::LinePool(const std::vector<glm::vec3>& wposs, const std::vector<glm::vec3>& dirs,
	const std::vector<glm::vec3>& tclrs, const std::vector<glm::vec3>& bclrs)
{
	count_ = wposs.size() * 2;
	std::vector<glm::vec3> positions; // start + end
	std::vector<glm::vec3> colors;    // start + end

	// the inputs better be the same size or i'll be mad
	for (int i = 0; i < wposs.size(); i++)
	{
		positions.push_back(wposs[i]);
		positions.push_back(wposs[i] + dirs[i]);
		colors.push_back(bclrs[i]);
		colors.push_back(tclrs[i]);
	}

	vao_ = new VAO();
	positions_ = new VBO(&positions[0], positions.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	colors_ =    new VBO(&colors[0]   , colors.size() * sizeof(glm::vec3)   , GL_STATIC_DRAW);

	positions_->Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	colors_->Bind();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
}

void LinePool::Draw() const
{
	vao_->Bind();
	glDrawArrays(GL_LINES, 0, count_);
}
