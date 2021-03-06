#include"Model.h"


const unsigned int width = 800; //Window width 
const unsigned int height = 800; //Window Height 


int main()
{
	// Initialize GLFW
	glfwInit();

	//Assign Version 3.3 Major and Minor as GLFW Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Activate Core Meaning we only access modern and no legacy content 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create Window with name etc
	GLFWwindow* window = glfwCreateWindow(width, height, "S5118418 Lighting Engine", NULL, NULL);

	// Error check - (If window fails to spawn)
	if (window == NULL)
	{
		std::cout << "GLFW Error, Please review core content" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set window to current context
	glfwMakeContextCurrent(window);



	// Initialise GLAD Library
	gladLoadGL();
	
	//Set viewport to current openGL window 
	glViewport(0, 0, width, height);





	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag"); //Default Program for renderering Object loader ETC
	Shader outliningProgram("outlining.vert", "outlining.frag"); //Create outline shaders (Additn to outline models)


	// Light Initialisation 
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);



	//Activate the Shader Program ONLY. If wanting the outline Also type outliningProgra.Activate();
	shaderProgram.Activate();

	//Assign Lighting to current context
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Set Depth Buffer to Less
	glDepthFunc(GL_LESS); //<< Depth Function
	glEnable(GL_STENCIL_TEST); //<< Stencel Function assignment 
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //Set up Stencel Operation 


	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	// - - - - Model Import - - - - 
	//Model Import functionalisty 
	 Model model("models/map/scene.gltf");




	 //Creation of FPS Count
	 double prevTime = 0.0;
	 double crntTime = 0.0;
	 double timeDiff;
	 unsigned int counter = 0;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// FPS Count
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "OpenGL CW s5118418 - " + FPS + "Frams - " + ms + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());
			prevTime = crntTime;
			counter = 0;
		}



		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); //Clear Each Frame

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Draw a model
		glStencilFunc(GL_ALWAYS, 1, 0xFF); //Stencel Buffer on Obj (disable primary and scale 
		glStencilMask(0xFF); //

		model.Draw(shaderProgram, camera);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);



		//outliningProgram.Activate();
		glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 1.08f);
		model.Draw(outliningProgram, camera);

		// Enable modifying of the stencil buffer
		glStencilMask(0xFF);
		// Clear stencil buffer
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		// Enable the depth buffer
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE); //Enable Face Culling
		glCullFace(GL_BACK); //Set Front to be visable rear to not be 
		glFrontFace(GL_CCW); //Set Counter clockwise Face Cull
  

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}