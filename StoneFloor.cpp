#include "StoneFloor.h"

StoneFloor::StoneFloor(Camera* camera)
{
	this->camera = camera;
}

StoneFloor::~StoneFloor()
{
	this->camera = nullptr;
}

void StoneFloor::Create(glm::vec3 position)
{
	this->position = position;
	//this->rotation = rotation;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	// Load the texture using any two methods
	Texture = loadDDS("stone-floor-001.dds");

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");


	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

}

void StoneFloor::Destroy()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void StoneFloor::Update()
{
	// Compute the MVP matrix from keyboard and mouse input
	ProjectionMatrix = camera->getProjectionMatrix();
	ViewMatrix = camera->getViewMatrix();
	//glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::translate(position);
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
}

void StoneFloor::Render()
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

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
