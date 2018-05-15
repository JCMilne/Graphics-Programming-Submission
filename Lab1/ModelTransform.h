#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "SceneCamera.h"

struct ModelTransform
{
public:
	ModelTransform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) //updates the values of the transform
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const  //returns the model matrix
	{
		glm::mat4 positionMatrix = glm::translate(position);
		glm::mat4 scaleMatrix = glm::scale(scale);
		glm::mat4 roationtX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotationY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotationZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotationMatrix = roationtX * rotationY * rotationZ;

		return positionMatrix * rotationMatrix * scaleMatrix;
	}

	inline glm::vec3* GetPosition() { return &position; } //getters
	inline glm::vec3* GetRotation() { return &rotation; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPosition(glm::vec3& position) { this->position = position; } // setters
	inline void SetRotation(glm::vec3& rotation) { this->rotation = rotation; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }
protected:
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};


