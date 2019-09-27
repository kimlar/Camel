#pragma once

// Include standard C++ headers
#include <vector>

// Include GL3W
#include <GL/gl3w.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>


// Include stuff
#include "Engine/Shader.h"
#include "Engine/Texture.h"
#include "Engine/Camera.h"

// Include common stuff
#include "Engine/vboindexer.h"
#include "Engine/quaternion_utils.h" // See quaternion_utils.cpp for RotationBetweenVectors, LookAt and RotateTowards

class SuzanneRotation
{
public:
	SuzanneRotation(Camera* camera);
	~SuzanneRotation(); // Note: should use virtual destructor

	void Create(glm::vec3 position);
	void Destroy();

	void Update();
	void Render();

	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;

	GLuint vertexPosition_modelspaceID;
	GLuint vertexUVID;
	GLuint vertexNormal_modelspaceID;

	GLuint Texture;
	GLuint TextureID;

	// Data from OBJ model loader
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;

	// Light
	GLuint LightID;

	glm::vec3 position;
	//glm::vec3 rotation;

	Camera* camera;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 RotationMatrix;
	glm::mat4 TranslationMatrix; // A bit to the left
	glm::mat4 ScalingMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;
	
	/////////////////////////////////////////////

	glm::vec3 gPosition1;
	glm::vec3 gOrientation1;

	glm::vec3 gPosition2;
	glm::quat gOrientation2;

	bool gLookAtOther;
};
