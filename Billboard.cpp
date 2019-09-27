#include "Billboard.h"

// Include our stuff
#include "Engine/objloader.h"

Billboard::Billboard(Camera* camera)
{
	this->camera = camera;
}

Billboard::~Billboard()
{
	this->camera = nullptr;
}

void Billboard::Create(glm::vec3 position)
{
	this->position = position;
	//this->rotation = rotation;

	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Billboard.vertexshader", "Billboard.fragmentshader");

	// Vertex shader
	CameraRight_worldspace_ID = glGetUniformLocation(programID, "CameraRight_worldspace");
	CameraUp_worldspace_ID = glGetUniformLocation(programID, "CameraUp_worldspace");
	ViewProjMatrixID = glGetUniformLocation(programID, "VP");
	BillboardPosID = glGetUniformLocation(programID, "BillboardPos");
	BillboardSizeID = glGetUniformLocation(programID, "BillboardSize");
	LifeLevelID = glGetUniformLocation(programID, "LifeLevel");

	TextureID = glGetUniformLocation(programID, "myTextureSampler");


	Texture = loadDDS("ExampleBillboard.dds");

	
	
	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

#ifdef DRAW_CUBE
	// Everything here comes from Tutorial 4
	cubeProgramID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
	cubeMatrixID = glGetUniformLocation(cubeProgramID, "MVP");

	glGenBuffers(1, &cubevertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubevertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertex_buffer_data), g_cube_vertex_buffer_data, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &cubecolorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubecolorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_color_buffer_data), g_cube_color_buffer_data, GL_DYNAMIC_DRAW);
#endif
}

void Billboard::Destroy()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &billboard_vertex_buffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
#ifdef DRAW_CUBE
	glDeleteProgram(cubeProgramID);
	glDeleteVertexArrays(1, &cubevertexbuffer);
	glDeleteVertexArrays(1, &cubecolorbuffer);
#endif

}

void Billboard::Update()
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

void Billboard::Render()
{
#ifdef DRAW_CUBE
	// Again : this is just Tutorial 4 !
	glDisable(GL_BLEND);
	glUseProgram(cubeProgramID);	
	//glm::mat4 cubeModelMatrix(1.0f);
	//cubeModelMatrix = glm::scale(cubeModelMatrix, glm::vec3(0.4f, 0.4f, 0.4f));
	//glm::mat4 cubeMVP = ProjectionMatrix * ViewMatrix * cubeModelMatrix;
	glm::mat4 cubeMVP = MVP;
	glUniformMatrix4fv(cubeMatrixID, 1, GL_FALSE, &cubeMVP[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, cubevertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cubecolorbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
#endif



	// We will need the camera's position in order to sort the particles
	// w.r.t the camera's distance.
	// There should be a getCameraPosition() function in common/controls.cpp, 
	// but this works too.
	glm::vec3 CameraPosition = camera->position; //glm::vec3 CameraPosition(glm::inverse(ViewMatrix)[3]);

	glm::mat4 ViewProjectionMatrix = MVP; //glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;





	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Use our shader
	glUseProgram(programID);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// This is the only interesting part of the tutorial.
	// This is equivalent to mlutiplying (1,0,0) and (0,1,0) by inverse(ViewMatrix).
	// ViewMatrix is orthogonal (it was made this way), 
	// so its inverse is also its transpose, 
	// and transposing a matrix is "free" (inversing is slooow)
	glUniform3f(CameraRight_worldspace_ID, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
	glUniform3f(CameraUp_worldspace_ID, ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);

	glUniform3f(BillboardPosID, 0.0f, 0.5f, 0.0f); // The billboard will be just above the cube
	glUniform2f(BillboardSizeID, 1.0f, 0.125f);     // and 1m*12cm, because it matches its 256*32 resolution =)

													// Generate some fake life level and send it to glsl
	float LifeLevel = sin(camera->window->fpsTime)*0.1f + 0.7f;
	glUniform1f(LifeLevelID, LifeLevel);

	glUniformMatrix4fv(ViewProjMatrixID, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);


	// Draw the billboard !
	// This draws a triangle_strip which looks like a quad.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0);
}
