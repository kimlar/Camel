#pragma once

// Include standard C++ headers
#include <vector>

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

// Include common stuff
#include "Engine/vboindexer.h"

class WindowGlass
{
public:
	WindowGlass(Camera* camera);
	~WindowGlass(); // Note: should use virtual destructor

	void Create(glm::vec3 position);
	void Destroy();

	void Update();
	void Render();

	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;

	GLuint Texture;
	GLuint TextureID;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;

	glm::vec3 position;
	//glm::vec3 rotation;

	Camera* camera;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;


	// Data from OBJ model loader
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;


	// Light
	GLuint LightID;
};
