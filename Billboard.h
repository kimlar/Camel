#pragma once

// Include standard C++ headers
#include <vector>

// Include GL3W
#include <GL/gl3w.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/norm.hpp>


// Include stuff
#include "Engine/Shader.h"
#include "Engine/Texture.h"
#include "Engine/Camera.h"

// Include common stuff
#include "Engine/vboindexer.h"

//#define DRAW_CUBE // Comment or uncomment this to simplify the code

class Billboard
{
public:
	Billboard(Camera* camera);
	~Billboard(); // Note: should use virtual destructor

	void Create(glm::vec3 position);
	void Destroy();

	void Update();
	void Render();


	glm::vec3 position;
	//glm::vec3 rotation;

	Camera* camera;

	
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;
	

	GLuint VertexArrayID;
	GLuint programID;

	GLuint CameraRight_worldspace_ID;
	GLuint CameraUp_worldspace_ID;
	GLuint ViewProjMatrixID;
	GLuint BillboardPosID;
	GLuint BillboardSizeID;
	GLuint LifeLevelID;

	GLuint TextureID;
	GLuint Texture;

	// The VBO containing the 4 vertices of the particles.
	const GLfloat g_vertex_buffer_data[12] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
	};

	GLuint billboard_vertex_buffer;

#ifdef DRAW_CUBE
	const GLfloat g_cube_vertex_buffer_data[108] = { -1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f, 1.0f, 1.0f,1.0f, 1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f, 1.0f,-1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,1.0f, 1.0f, 1.0f,1.0f,-1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f, 1.0f, 1.0f,1.0f,-1.0f, 1.0f,1.0f, 1.0f, 1.0f,1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,1.0f, 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f,1.0f,-1.0f, 1.0f };
	const GLfloat g_cube_color_buffer_data[108] = { 0.583f,  0.771f,  0.014f,0.609f,  0.115f,  0.436f,0.327f,  0.483f,  0.844f,0.822f,  0.569f,  0.201f,0.435f,  0.602f,  0.223f,0.310f,  0.747f,  0.185f,0.597f,  0.770f,  0.761f,0.559f,  0.436f,  0.730f,0.359f,  0.583f,  0.152f,0.483f,  0.596f,  0.789f,0.559f,  0.861f,  0.639f,0.195f,  0.548f,  0.859f,0.014f,  0.184f,  0.576f,0.771f,  0.328f,  0.970f,0.406f,  0.615f,  0.116f,0.676f,  0.977f,  0.133f,0.971f,  0.572f,  0.833f,0.140f,  0.616f,  0.489f,0.997f,  0.513f,  0.064f,0.945f,  0.719f,  0.592f,0.543f,  0.021f,  0.978f,0.279f,  0.317f,  0.505f,0.167f,  0.620f,  0.077f,0.347f,  0.857f,  0.137f,0.055f,  0.953f,  0.042f,0.714f,  0.505f,  0.345f,0.783f,  0.290f,  0.734f,0.722f,  0.645f,  0.174f,0.302f,  0.455f,  0.848f,0.225f,  0.587f,  0.040f,0.517f,  0.713f,  0.338f,0.053f,  0.959f,  0.120f,0.393f,  0.621f,  0.362f,0.673f,  0.211f,  0.457f,0.820f,  0.883f,  0.371f,0.982f,  0.099f,  0.879f };

	GLuint cubeProgramID;
	GLuint cubeMatrixID;
	GLuint cubevertexbuffer;
	GLuint cubecolorbuffer;
#endif

};
