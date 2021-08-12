#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

//Camera Class for moving around a 3D space
class Camera
{
	public:
		glm::vec3 Position; //Current Position stored X, Y, Z
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f); //Orientation (Used to lock orientation preventing upsidown)
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); //UpSpeed for vertical Movement 
		glm::mat4 cameraMatrix = glm::mat4(1.0f); //Matrix for storing core values

		 
		bool firstClick = true; //Bool Value for re-centering camera on click 

		int width; //Width of Cam view
		int height; //Height of Cam View

		float speed = 0.1; //Speed of camera 
		float sensitivity = 100.0f; //Mouse sensitivity

		Camera(int width, int height, glm::vec3 position); //Camera Struct

		void updateMatrix(float FOVdeg, float nearPlane, float farPlane); //Movement of Camera
		void Matrix(Shader& shader, const char* uniform); //Movement in 3D Plane
		void Inputs(GLFWwindow* window); //Get Keyboard Inputs from Keypads. 

};


#endif
