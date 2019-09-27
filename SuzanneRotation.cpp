#include "SuzanneRotation.h"

// Include our stuff
#include "Engine/objloader.h"

SuzanneRotation::SuzanneRotation(Camera* camera)
{
	this->camera = camera;

	gPosition1 = glm::vec3(-1.5f, 0.0f, 0.0f);

	gPosition2 = glm::vec3(1.5f, 0.0f, 0.0f);

	gLookAtOther = true;
}

SuzanneRotation::~SuzanneRotation()
{
	this->camera = nullptr;
}

void SuzanneRotation::Create(glm::vec3 position)
{
	this->position = position;
	//this->rotation = rotation;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");

	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	vertexUVID = glGetAttribLocation(programID, "vertexUV");
	vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

	// Load the texture
	Texture = loadDDS("suzanne-uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);

	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	// Load it into a VBO

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

}

void SuzanneRotation::Destroy()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);

	glDeleteVertexArrays(1, &VertexArrayID);
}

void SuzanneRotation::Update()
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

void SuzanneRotation::Render()
{
	// Use our shader
	glUseProgram(programID);

	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	ViewMatrix = glm::lookAt(
		glm::vec3(0, 0, 7), // Camera is here
		glm::vec3(0, 0, 0), // and looks here
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		vertexPosition_modelspaceID,  // The attribute we want to configure
		3,                            // size
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		vertexUVID,                   // The attribute we want to configure
		2,                            // size : U+V => 2
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		vertexNormal_modelspaceID,    // The attribute we want to configure
		3,                            // size
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glm::vec3 lightPos = glm::vec3(4, 4, 4);
	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

	{ // Euler

		//// As an example, rotate around the vertical axis at 180'/sec
		//gOrientation1.y += 3.14159f / 2.0f * deltaTime;
		gOrientation1.y += 3.14159f / 2.0f * camera->window->deltaTime;

		// Build the model matrix
		RotationMatrix = glm::eulerAngleYXZ(gOrientation1.y, gOrientation1.x, gOrientation1.z);
		TranslationMatrix = glm::translate(glm::mat4(), gPosition1); // A bit to the left
		ScalingMatrix = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			(GLsizei)indices.size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);

	}
	{ // Quaternion

	  // It the box is checked...
		if (gLookAtOther) {
			glm::vec3 desiredDir = gPosition1 - gPosition2;
			glm::vec3 desiredUp = glm::vec3(0.0f, 1.0f, 0.0f); // +Y

													 // Compute the desired orientation
			glm::quat targetOrientation = glm::normalize(LookAt(desiredDir, desiredUp));

			// And interpolate
			gOrientation2 = RotateTowards(gOrientation2, targetOrientation, 1.0f*camera->window->deltaTime);
		}

		RotationMatrix = glm::mat4_cast(gOrientation2);
		TranslationMatrix = glm::translate(glm::mat4(), gPosition2); // A bit to the right
		ScalingMatrix = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);


		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			(GLsizei)indices.size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}
