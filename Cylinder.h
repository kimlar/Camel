#pragma once

// Include standard headers
//#include <stdio.h>
//#include <stdlib.h>
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
#include "Engine/tangentspace.h"


class Cylinder
{
public:
	Cylinder(Camera* camera);
	~Cylinder();

	void Create(glm::vec3 position);
	void Destroy();
	
	void Render();
private:
		
	GLuint VertexArrayID;
	
	// Create and compile our GLSL program from the shaders
	GLuint programID;

	// Get a handle for our "MVP" uniform
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint ModelView3x3MatrixID;

	// Load the texture
	GLuint DiffuseTexture;
	GLuint NormalTexture;
	GLuint SpecularTexture;

	// Get a handle for our "myTextureSampler" uniform
	GLuint DiffuseTextureID;
	GLuint NormalTextureID;
	GLuint SpecularTextureID;

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	std::vector<glm::vec3> indexed_tangents;
	std::vector<glm::vec3> indexed_bitangents;


	// Load it into a VBO

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint tangentbuffer;
	GLuint bitangentbuffer;

	// Generate a buffer for the indices as well
	GLuint elementbuffer;

	// Get a handle for our "LightPosition" uniform
	GLuint LightID;

	///////////////////////////////////////////////////////////////


	// Compute the MVP matrix from keyboard and mouse input
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 ModelViewMatrix;
	glm::mat3 ModelView3x3Matrix;
	glm::mat4 MVP;

	///////////////////////////////////////////////////////////////

	Camera* camera;

	glm::vec3 position;
};