#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

struct Vertex
{
	glm::vec3 position; //Position of Vertices 
	glm::vec3 normal; //Normal storage
	glm::vec3 color; //Albedo storage
	glm::vec2 texUV; //UV data storage
};
 
//VBO class to better store data types
class VBO
{
	public:
		GLuint ID;

		VBO(std::vector<Vertex>& vertices);
		
		void Bind();
		void Unbind();
		void Delete();
};

#endif

