#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

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

	glClearColor(0.07f, 0.13, 0.17f, 1.0f); //Set background Colour 
	glClear(GL_COLOR_BUFFER_BIT); //Change Buffer from Front to Back
	glfwSwapBuffers(window); //Swap buffer




	while (!glfwWindowShouldClose(window)) //While window is open
	{
		glfwPollEvents(); //Window loop (Similar to DeltaTime)
	}


	glfwDestroyWindow(window); //Destroy Window object
	glfwTerminate(); //Terminate GLFW
	return 0;
}