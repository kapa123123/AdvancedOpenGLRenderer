#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

//Class to accuratley take in a mesh from an external file (Root)
class Mesh
{
public: 
	std::vector <Vertex> vertices; //Used by the vert shader for Implimentation
	std::vector <GLuint> indices; //Used by the vert shader for Implimentation
	std::vector <Texture> textures; //Addition for Texture import unctionality

	// Put VAO in area to for public access
	VAO VAO;

	//Create mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draw the mesh to the screeen
	void Draw
	(
		Shader& shader, 
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)

	);
};

#endif