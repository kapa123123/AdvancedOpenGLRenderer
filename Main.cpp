#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";





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


	// Create Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Create a shader and create ref Value
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Assign Shader
	glCompileShader(vertexShader); //Compile Shader into Machine Code (For GPU)

	//Create Frag Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Wrap Vertex and Frag into two shader program to be used by OpenGL
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram); //Link both shders into a simgle program

	//Now shaders are linked, delete both shaders (As both are in program)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Assigning Verticies (GLFloat for Security)
	GLfloat verticies[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	// Create Vertex Buffer Object for usage between CPU and GPU respectively
	GLuint VAO, VBO, EBO; 


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW); //Draw Verticies




	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //Way to communicate with the shader from external
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//End of VAO and VBO 

	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Set background Colour 
	//glClear(GL_COLOR_BUFFER_BIT); //Change Buffer from Front to Back
	//glfwSwapBuffers(window); //Swap buffer




	while (!glfwWindowShouldClose(window)) //Main program loop
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Background Colour
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents(); //Window loop (Similar to DeltaTime)
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);


	glfwDestroyWindow(window); //Destroy Window object
	glfwTerminate(); //Terminate GLFW
	return 0;
}