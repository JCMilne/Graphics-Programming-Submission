#include "ObjectMesh.h"
#include <vector>


void ObjectMesh::initialise(ObjectVertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indicesCount)  //initalises the model
{
	IndexedModel model;

	for (unsigned int i = 0; i < vertexCount; i++)
	{
		model.positions.push_back(*vertices[i].GetPosition());
		model.texCoords.push_back(*vertices[i].GetTextureCoordinates());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < indicesCount; i++)
		model.indices.push_back(indices[i]);

	initaliseModel(model);
}

void ObjectMesh::initaliseModel(const IndexedModel& model)
{

	VAObjectCount = model.indices.size();

	glGenVertexArrays(1, &VAObject); //generate a vertex array object and store it in the VAO
	glBindVertexArray(VAObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(BufferCount, VABuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glBindBuffer(GL_ARRAY_BUFFER, VABuffers[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VABuffers[VertexBuffer_TextureCoordinates]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VABuffers[VertexBuffer_Normal]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VABuffers[VertexBuffer_Index]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our VAO
}

ObjectMesh::ObjectMesh()  //sets va object count to null
{
	VAObjectCount = NULL;
}

void ObjectMesh::loadModelFromFile(const std::string& filename)  //loads a model from an external file
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initaliseModel(model);
}

ObjectMesh::~ObjectMesh()
{
	glDeleteVertexArrays(1, &VAObject); // deletes the arrays
}

void ObjectMesh::drawModel()  //draws the model to the screen
{
	glBindVertexArray(VAObject);

	glDrawElements(GL_TRIANGLES, VAObjectCount, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, VAObjectCount);

	glBindVertexArray(0);
}

