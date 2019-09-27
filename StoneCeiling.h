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

class StoneCeiling
{
public:
	StoneCeiling(Camera* camera);
	~StoneCeiling(); // Note: should use virtual destructor

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
	const GLfloat g_vertex_buffer_data[6 * 3] = {
		-1.0f,-1.0f,1.0f, //0
		-1.0f,-1.0f,-1.0f, //2
		1.0f,-1.0f,1.0f, //1
		1.0f,-1.0f,1.0f, //4
		-1.0f, -1.0f,-1.0f, //3
		1.0f, -1.0f,-1.0f, //5
	};

	// Two UV coordinatesfor each vertex. They were created with Blender.
	const GLfloat g_uv_buffer_data[6 * 2] = {
		0.000000f, 0.000000f,
		1.000000f, 0.000000f,
		0.000000f, 1.000000f,
		0.000000f, 1.000000f,
		1.000000f, 0.000000f,
		1.000000f, 1.000000f,
	};

};
