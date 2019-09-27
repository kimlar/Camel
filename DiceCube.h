#pragma once

// Include GL3W
#include <GL/gl3w.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// Include stuff
#include "Engine/Shader.h"
#include "Engine/Texture.h"
#include "Engine/Camera.h"

class DiceCube
{
public:
	DiceCube(Camera* camera);
	~DiceCube(); // Note: should use virtual destructor

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

	Camera* camera;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	const GLfloat g_vertex_buffer_data[36 * 3] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	// Two UV coordinatesfor each vertex. They were created with Blender.
	const GLfloat g_uv_buffer_data[36 * 2] = {
		0.000059f, 0.000004f,
		0.000103f, 0.336048f,
		0.335973f, 0.335903f,
		1.000023f, 0.000013f,
		0.667979f, 0.335851f,
		0.999958f, 0.336064f,
		0.667979f, 0.335851f,
		0.336024f, 0.671877f,
		0.667969f, 0.671889f,
		1.000023f, 0.000013f,
		0.668104f, 0.000013f,
		0.667979f, 0.335851f,
		0.000059f, 0.000004f,
		0.335973f, 0.335903f,
		0.336098f, 0.000071f,
		0.667979f, 0.335851f,
		0.335973f, 0.335903f,
		0.336024f, 0.671877f,
		1.000004f, 0.671847f,
		0.999958f, 0.336064f,
		0.667979f, 0.335851f,
		0.668104f, 0.000013f,
		0.335973f, 0.335903f,
		0.667979f, 0.335851f,
		0.335973f, 0.335903f,
		0.668104f, 0.000013f,
		0.336098f, 0.000071f,
		0.000103f, 0.336048f,
		0.000004f, 0.671870f,
		0.336024f, 0.671877f,
		0.000103f, 0.336048f,
		0.336024f, 0.671877f,
		0.335973f, 0.335903f,
		0.667969f, 0.671889f,
		1.000004f, 0.671847f,
		0.667979f, 0.335851f
	};

};
