#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class EBO
{
public:
	GLuint ID; //Identify type in EBO 
	EBO(std::vector<GLuint>& indices);

	void Bind(); //Bind to the EBO
	void Unbind(); //Clear the EBO
	void Delete(); //Delete program 
};




#endif

