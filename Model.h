#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <json/json.h>
#include "Mesh.h"

using json = nlohmann::json; //JSON External Library, Used for GLTF file import 

class Model
{
public:
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera); //Draw Model to screen

private:
	const char* file; //Name of File

	std::vector<unsigned char> data; //Data Type of File

	json JSON; //External Library struct 

	std::vector<Mesh> meshes; //Name mesh for indovidualisation

	std::vector<glm::vec3> translationsMeshes; //XYZ Location 

	std::vector<glm::quat> rotationsMeshes; // Rotational data storage

	std::vector<glm::vec3> scalesMeshes; //Scale to World mesh data

	std::vector<glm::mat4> matricesMeshes; //All data types 


	std::vector<std::string> loadedTexName; //Load check to not take up too much data

	std::vector<Texture> loadedTex; //Loaded Texture ready to be utilised in later implimentation 

	void loadMesh(unsigned int indMesh); //Load mesh into program 

	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f)); //Move around on a node struct
	
	std::vector<unsigned char> getData();
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();


	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions, 
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs

	);

	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

#endif // ! MODEL_CLASS_H
