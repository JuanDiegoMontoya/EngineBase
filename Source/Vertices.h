#pragma once

namespace Vertices
{
	static const GLfloat cube_vertices_light[] =
	{
		// f
		-.5f,-.5f,.5f, // lbf
		 .5f,-.5f,.5f, // rbf
		-.5f, .5f,.5f, // ltf
		 .5f, .5f,.5f, // rtf

		// n
		-.5f,-.5f,-.5f, // lbn
		 .5f,-.5f,-.5f, // rbn
		-.5f, .5f,-.5f, // ltn
		 .5f, .5f,-.5f, // rtn

		// l
		-.5f,-.5f,-.5f, // lbn
		-.5f,-.5f, .5f, // lbf
		-.5f, .5f,-.5f, // ltn
		-.5f, .5f, .5f, // ltf

		// r
		 .5f,-.5f,-.5f, // rbn
		 .5f,-.5f, .5f, // rbf
		 .5f, .5f,-.5f, // rtn
		 .5f, .5f, .5f, // rtf

		// t
		-.5f, .5f,-.5f, // ltn
		-.5f, .5f, .5f, // ltf
		 .5f, .5f,-.5f, // rtn
		 .5f, .5f, .5f, // rtf

		// b
		-.5f,-.5f,-.5f, // lbn
		-.5f,-.5f, .5f, // lbf
		 .5f,-.5f,-.5f, // rbn
		 .5f,-.5f, .5f, // rbf
	};

	// f n l r t b
	static const GLubyte cube_indices_light_ccw[] =
	{
		0, 2, 1, 2, 3, 1, // f
		0, 1, 2, 1, 3, 2, // n
		0, 2, 1, 1, 2, 3, // l
		0, 1, 2, 1, 3, 2, // r
		0, 2, 1, 2, 3, 1, // t
		0, 1, 2, 1, 3, 2  // b
	};

	static const GLubyte cube_indices_light_cw[] =
	{
		1, 2, 0, 1, 3, 2, // f
		2, 1, 0, 2, 3, 1, // n
		1, 2, 0, 3, 2, 1, // l
		2, 1, 0, 2, 3, 1, // r
		1, 2, 0, 1, 3, 2, // t
		2, 1, 0, 2, 3, 1  // b
	};

	static const float cube[] =
	{
		// Back face (-Z)
		-0.5f, -0.5f, -0.5f, // Bottom-left
		 0.5f,  0.5f, -0.5f, // top-right
		 0.5f, -0.5f, -0.5f, // bottom-right         
		 0.5f,  0.5f, -0.5f, // top-right
		-0.5f, -0.5f, -0.5f, // bottom-left
		-0.5f,  0.5f, -0.5f, // top-left

		// Front face (+Z)
		-0.5f, -0.5f,  0.5f, // bottom-left
		 0.5f, -0.5f,  0.5f, // bottom-right
		 0.5f,  0.5f,  0.5f, // top-right
		 0.5f,  0.5f,  0.5f, // top-right
		-0.5f,  0.5f,  0.5f, // top-left
		-0.5f, -0.5f,  0.5f, // bottom-left

		// Left face (-X)
		-0.5f,  0.5f,  0.5f, // top-right
		-0.5f,  0.5f, -0.5f, // top-left
		-0.5f, -0.5f, -0.5f, // bottom-left
		-0.5f, -0.5f, -0.5f, // bottom-left
		-0.5f, -0.5f,  0.5f, // bottom-right
		-0.5f,  0.5f,  0.5f, // top-right

		// Right face (+X)
		 0.5f,  0.5f,  0.5f, // top-left
		 0.5f, -0.5f, -0.5f, // bottom-right
		 0.5f,  0.5f, -0.5f, // top-right         
		 0.5f, -0.5f, -0.5f, // bottom-right
		 0.5f,  0.5f,  0.5f, // top-left
		 0.5f, -0.5f,  0.5f, // bottom-left     

		// Bottom face (-Y)
		-0.5f, -0.5f, -0.5f, // top-right
		 0.5f, -0.5f, -0.5f, // top-left
		 0.5f, -0.5f,  0.5f, // bottom-left
		 0.5f, -0.5f,  0.5f, // bottom-left
		-0.5f, -0.5f,  0.5f, // bottom-right
		-0.5f, -0.5f, -0.5f, // top-right

		// Top face (+Y)
		-0.5f,  0.5f, -0.5f, // top-left
		 0.5f,  0.5f,  0.5f, // bottom-right
		 0.5f,  0.5f, -0.5f, // top-right     
		 0.5f,  0.5f,  0.5f, // bottom-right
		-0.5f,  0.5f, -0.5f, // top-left
		-0.5f,  0.5f,  0.5f  // bottom-left    
	};

	static const float skybox[] =
	{
		// positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
}