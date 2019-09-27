#include "LightMap.h"

// Include our stuff
#include "Engine/objloader.h"

LightMap::LightMap(Camera* camera)
{
	this->camera = camera;
}

LightMap::~LightMap()
{
	this->camera = nullptr;
}

void LightMap::Create(glm::vec3 position)
{
	this->position = position;
	//this->rotation = rotation;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShaderLOD.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	// Load the texture
	Texture = loadDDS("lightmap.dds");

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	bool res = loadOBJ("room.obj", vertices, uvs, normals);

	// Load it into a VBO

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

}

void LightMap::Destroy()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void LightMap::Update()
{
	/*
	// Compute the MVP matrix from keyboard and mouse input
	ProjectionMatrix = camera->getProjectionMatrix();
	ViewMatrix = camera->getViewMatrix();
	//glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::translate(position);
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	*/

	// Compute the MVP matrix from keyboard and mouse input
	ProjectionMatrix = camera->getProjectionMatrix();
	ViewMatrix = camera->getViewMatrix();
	ModelMatrix = glm::translate(position); //glm::mat4(1.0);
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
}

void LightMap::Render()
{
	// Use our shader
	glUseProgram(programID);

	/*
	// Compute the MVP matrix from keyboard and mouse input
	glm::mat4 ProjectionMatrix = camera->getProjectionMatrix();
	glm::mat4 ViewMatrix = camera->getViewMatrix();
	//glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 ModelMatrix = glm::translate(position);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	*/




	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);




    // Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
