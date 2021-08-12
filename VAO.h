#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

//VAO Class
class VAO
{
	public:
		GLuint ID;
		VAO();

		//Link VBO's Into a single structure
		void LinkAttrib(VBO& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizeiptr stride, void* offset);

		//Bind the VBO to the main function 
		void Bind();

		//Unbind the VBO to clear the structure 
		void Unbind();

		//Delete at end of main to clean data 
		void Delete();

};

#endif