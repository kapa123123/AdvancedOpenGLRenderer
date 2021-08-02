#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"


//Assigning Verticies (GLFloat for Security)
GLfloat verticies[] =
{
	//   COORDINATES		     Colours			 TexCoord
	-0.5f, -0.5f, 0.0f,		 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		 // Lower left corner
	-0.5f,  0.5f, 0.0f,		 0.0f, 1.0f, 0.0f,		0.0f, 1.0f,		 // Upper Left right corner
	 0.5f,  0.5f, 0.0f,		 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,	     // Upper Right corner
	 0.5f, -0.5f, 0.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f,     // Lowwer  left

};

GLuint indices[] =
{
	0, 2, 1, //Upper 
	0, 3, 2	 //Lower
};



int main()
{
	glfwInit(); //Initialise GLFW 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Tell GLFW which majore version it will be using (3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Tell GLFW which minor version we will be using (3)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Select Core OpenGL profile


	//Create a Window 
	GLFWwindow* window = glfwCreateWindow(800, 800, "Advanced Render", NULL, NULL);
	
	//Check window creation is successful
	if (window == NULL)
	{
		std::cout << "Window Error Initialisation Failed";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //Make window part of current Context

	gladLoadGL(); //Initialise GLAD after window is created

	glViewport(0, 0, 800, 800); //Set size of Viewport for both OpenGL and GLAD

	Shader shaderProgram("default.vert", "default.frag");

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

	GLint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texturing

	Texture spongeBob("test_image.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	spongeBob.texUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window)) //Main program loop
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Background Colour
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);

		spongeBob.Bind();

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents(); //Window loop (Similar to DeltaTime)
	}
	 
	//Clean Up after project Closes
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	spongeBob.Delete();
	shaderProgram.Delete();


	glfwDestroyWindow(window); //Destroy Window object
	glfwTerminate(); //Terminate GLFW
	return 0;
}