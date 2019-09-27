#pragma once

// Include GL3W
#include <GL/gl3w.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// Include stuff
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

class UI
{
public:
	UI(Window* window);
	~UI(); // Note: should use virtual destructor

	void Create(glm::vec3 position);
	void Destroy();

	void Update();
	void Render();

	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;

	GLuint Texture;
	GLuint TextureID;

	GLuint vertexbuffer;
	GLuint uvbuffer;

	glm::vec3 position;
	//glm::vec3 rotation;

	Window* window;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	const GLfloat g_vertex_buffer_data[6*6 * 3] = {
		/*
		-1.0f,1.0f, 0.0f, // left top
		-1.0f,-1.0f, 0.0f, // left bottom
		1.0f,1.0f, 0.0f, // right top
		1.0f,1.0f, 0.0f, // right top
		-1.0f, -1.0f, 0.0f, // left bottom
		1.0f, -1.0f, 0.0f, // right bottom
		*/

		// 0
		-1.000000f,  1.000000f, 0.0f, // left top
		-1.000000f,  0.666667f, 0.0f, // left bottom
		 1.000000f,  1.000000f, 0.0f, // right top
		 1.000000f,  1.000000f, 0.0f, // right top
		-1.000000f,  0.666667f, 0.0f, // left bottom
		 1.000000f,  0.666667f, 0.0f, // right bottom
		// 1
		-1.000000f,  0.666667f, 0.0f, // left top
		-1.000000f,  0.333333f, 0.0f, // left bottom
		 1.000000f,  0.666667f, 0.0f, // right top
		 1.000000f,  0.666667f, 0.0f, // right top
		-1.000000f,  0.333333f, 0.0f, // left bottom
		 1.000000f,  0.333333f, 0.0f, // right bottom
		// 2
		-1.000000f,  0.333333f, 0.0f, // left top
		-1.000000f,  0.000000f, 0.0f, // left bottom
		 1.000000f,  0.333333f, 0.0f, // right top
		 1.000000f,  0.333333f, 0.0f, // right top
		-1.000000f,  0.000000f, 0.0f, // left bottom
		 1.000000f,  0.000000f, 0.0f, // right bottom
		// 3
		-1.000000f,  0.000000f, 0.0f, // left top
		-1.000000f, -0.333333f, 0.0f, // left bottom
		 1.000000f,  0.000000f, 0.0f, // right top
		 1.000000f,  0.000000f, 0.0f, // right top
		-1.000000f, -0.333333f, 0.0f, // left bottom
		 1.000000f, -0.333333f, 0.0f, // right bottom
		// 4
		-1.000000f, -0.333333f, 0.0f, // left top
		-1.000000f, -0.666667f, 0.0f, // left bottom
		 1.000000f, -0.333333f, 0.0f, // right top
		 1.000000f, -0.333333f, 0.0f, // right top
		-1.000000f, -0.666667f, 0.0f, // left bottom
		 1.000000f, -0.666667f, 0.0f, // right bottom
		// 5
		-1.000000f, -0.666667f, 0.0f, // left top
		-1.000000f, -1.000000f, 0.0f, // left bottom
		 1.000000f, -0.666667f, 0.0f, // right top
		 1.000000f, -0.666667f, 0.0f, // right top
		-1.000000f, -1.000000f, 0.0f, // left bottom
		 1.000000f, -1.000000f, 0.0f, // right bottom
	};

	// Two UV coordinatesfor each vertex. They were created with Blender.
	const GLfloat g_uv_buffer_data[6*6 * 2] = {
		/*
		0.000000f, 0.000000f,
		0.000000f, 1.000000f,
		1.000000f, 0.000000f,
		1.000000f, 0.000000f,
		0.000000f, 1.000000f,
		1.000000f, 1.000000f,
		*/

		// 0
		0.000000f, 0.000000f,
		0.000000f, 0.166667f,
		1.000000f, 0.000000f,
		1.000000f, 0.000000f,
		0.000000f, 0.166667f,
		1.000000f, 0.166667f,
		// 1
		0.000000f, 0.166667f,
		0.000000f, 0.333333f,
		1.000000f, 0.166667f,
		1.000000f, 0.166667f,
		0.000000f, 0.333333f,
		1.000000f, 0.333333f,
		// 2
		0.000000f, 0.333333f,
		0.000000f, 0.500000f,
		1.000000f, 0.333333f,
		1.000000f, 0.333333f,
		0.000000f, 0.500000f,
		1.000000f, 0.500000f,
		// 3
		0.000000f, 0.500000f,
		0.000000f, 0.666667f,
		1.000000f, 0.500000f,
		1.000000f, 0.500000f,
		0.000000f, 0.666667f,
		1.000000f, 0.666667f,
		// 4
		0.000000f, 0.666667f,
		0.000000f, 0.833333f,
		1.000000f, 0.666667f,
		1.000000f, 0.666667f,
		0.000000f, 0.833333f,
		1.000000f, 0.833333f,
		// 5
		0.000000f, 0.833333f,
		0.000000f, 1.000000f,
		1.000000f, 0.833333f,
		1.000000f, 0.833333f,
		0.000000f, 1.000000f,
		1.000000f, 1.000000f,
	};


	int buttonFrame;
	int buttonDelay;
};
