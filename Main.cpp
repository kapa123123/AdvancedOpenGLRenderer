#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


//Assigning Verticies (GLFloat for Security)
GLfloat verticies[] =
{
	//		   COORDINATES								Colours 
	-0.5f, -0.5f * float(sqrt(3)) / 3,		 0.0f, 0.8f, 0.3f,  0.02f,		 // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) / 3,		 0.0f, 0.8f, 0.3f,  0.02f,		 // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3,	 0.0f, 1.0f, 0.6f,  0.32f,		 // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) / 6,		 0.0f, 0.9f, 0.45f, 0.17f,		 // Inner left
	 0.25f, 0.5f * float(sqrt(3)) / 6,		 0.0f, 0.9f, 0.45f, 0.17f,		 // Inner right
	 0.0f, -0.5f * float(sqrt(3)) / 3,		 0.0f, 0.8f, 0.3f,  0.02f		 // Inner down
};

GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
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

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	while (!glfwWindowShouldClose(window)) //Main program loop
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Background Colour
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents(); //Window loop (Similar to DeltaTime)
	}

	//Clean Up after project Closes
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();


	glfwDestroyWindow(window); //Destroy Window object
	glfwTerminate(); //Terminate GLFW
	return 0;
}