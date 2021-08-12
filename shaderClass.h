#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H


#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename); //Read text file name for Shader Addtition 

class Shader
{
	public: 
		GLuint ID; //ID number for the shader Class
		Shader(const char* vertexFile, const char* fragmentFile); //Shader type and creation 

		void Activate(); //Activation of Shader (In Main)
		void Delete(); //Delete Shader to properly clean ram (End of Main)

	private:
		void compileErrors(unsigned int shader, const char* type); //Fail tester

};


#endif