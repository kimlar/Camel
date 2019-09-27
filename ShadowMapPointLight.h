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

class ShadowMapPointLight
{
public:
	ShadowMapPointLight(Camera* camera);
	~ShadowMapPointLight(); // Note: should use virtual destructor

	void Create(glm::vec3 position);
	void Destroy();

	void Update();
	void Render();

	glm::vec3 position;
	Camera* camera;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

	/////////////////////////////////////////////

	GLuint VertexArrayID;
	GLuint depthProgramID;
	GLuint depthMatrixID;

	GLuint Texture;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;

	// ---------------------------------------------
	// Render to Texture - specific code begins here
	// ---------------------------------------------

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName;
	GLuint depthTexture;

	GLuint quad_vertexbuffer;

	GLuint quad_programID;
	GLuint texID;
	GLuint programID;
	GLuint TextureID;

	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint DepthBiasID;
	GLuint ShadowMapID;

	GLuint lightInvDirID;
};


