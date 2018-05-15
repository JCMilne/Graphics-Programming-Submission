#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct ObjectVertex
{
public:
	ObjectVertex(const glm::vec3& position, const glm::vec2& textureCoordinates)  //sets the variables of the vertex
	{
		this->position = position;
		this->textureCoordinates = textureCoordinates;
		this->objectNormal = objectNormal;
	}

	glm::vec3* GetPosition() { return &position; }  //gets the individual variables
	glm::vec2* GetTextureCoordinates() { return &textureCoordinates; }
	glm::vec3* GetNormal() { return &objectNormal; }

private:
	glm::vec3 position;
	glm::vec2 textureCoordinates;
	glm::vec3 objectNormal;
};

class ObjectMesh
{
public:
	ObjectMesh();
	~ObjectMesh();


	void drawModel();
	void initialise(ObjectVertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indiciesCount);
	void loadModelFromFile(const std::string& filename);
	void initaliseModel(const IndexedModel& model);


private:
	enum
	{
		POSITION_VERTEXBUFFER,
		VertexBuffer_TextureCoordinates,
		VertexBuffer_Normal,
		VertexBuffer_Index,
		BufferCount
	};

	GLuint VAObject;
	GLuint VABuffers[BufferCount]; // create our array of buffers
	unsigned int VAObjectCount; //how much of the VAObject do we want to draw
};