#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h> //STB Utilised for Image processing and Import of Textures
#include <glm/glm.hpp> //GLM Math's library for 3D Matricis 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

//Assigning Verticies (GLFloat for Security)
GLfloat verticies[] =
{
	//   COORDINATES		     Colours			 TexCoord
	-0.5f, 0.0f, 0.5f,		 0.83f, 0.70f, 0.44f,		0.0f, 0.0f,		
	-0.5f, 0.0f, -0.5f,		 0.83f, 0.70f, 0.44f,		5.0f, 0.0f,		
	 0.5f,  0.0f, -0.5f,	 0.83f, 0.70f, 0.44f,	    0.0f, 0.0f,	    
	 0.5f, 0.0f, 0.5f,		 0.83f, 0.70f, 0.44f,		5.0f, 0.0f,  
	 0.0f, 0.8f, 0.0f,		 0.92f, 0.86f, 0.76f,		2.5f, 5.0f,

};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4,
};



int main()
{
	glfwInit(); //Initialise GLFW 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Tell GLFW which majore version it will be using (3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Tell GLFW which minor version we will be using (3)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Select Core OpenGL profile


	//Create a Window 
	GLFWwindow* window = glfwCreateWindow(width, height, "Advanced Render", NULL, NULL);
	
	//Check window creation is successful
	if (window == NULL)
	{
		std::cout << "Window Error Initialisation Failed";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //Make window part of current Context

	gladLoadGL(); //Initialise GLAD after window is created

	glViewport(0, 0, width, height); //Set size of Viewport for both OpenGL and GLAD

	Shader shaderProgram("default.vert", "default.frag");

	//
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(verticies, sizeof(verticies));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	

	// Texture assignment 
	Texture spongeBob("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	spongeBob.texUnit(shaderProgram, "tex0", 0);


	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) //Main program loop
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Background Colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");





		//3D space Data

		//glm::mat4 model = glm::mat4(1.0f); //Initialisation of Model matrix
		//glm::mat4 view = glm::mat4(1.0f); //Initialisation of View Matrix
		//glm::mat4 proj = glm::mat4(1.0f); //Initialisation of Projection Matrix

		spongeBob.Bind();

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents(); //Window loop (Similar to DeltaTime)
	}
	 
	//Clean Up after project Closes
	VAO1.Delete(); // Delete VAO
	VBO1.Delete(); //Delete VBO's
	EBO1.Delete(); //Delete EBO
	spongeBob.Delete(); //Delete Texture
	shaderProgram.Delete(); //Delete Shaders


	glfwDestroyWindow(window); //Destroy Window object
	glfwTerminate(); //Terminate GLFW
	return 0;
}