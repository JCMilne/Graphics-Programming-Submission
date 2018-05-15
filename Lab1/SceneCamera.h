#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct SceneCamera
{
public:
	SceneCamera()
	{
	}	
	
	inline glm::mat4 GetView() const   //returns the view marix
	{
		return glm::lookAt(CameraPosition, CameraPosition + CameraForward, CameraUp);
	}

	void createCamera(const glm::vec3& position, float FieldOfView, float AspectRatio, float nearClipPlane, float farClipPlane)  //initalises all the cameras variables
	{
		this->CameraPosition = position;
		this->CameraForward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		this->CameraProjection = glm::perspective(FieldOfView, AspectRatio, nearClipPlane, farClipPlane);
	}

	inline glm::mat4 GetProjection() const  //returns the projection matrix
	{
		return CameraProjection;
	}
	
	glm::vec3 getPos()  //returns thecamers position
	{
		return this->CameraPosition;
	}

	inline glm::mat4 GetViewProjection() const  //returns the view projection matrix
	{
		return CameraProjection * GetView();
	}

protected:
private:
	glm::mat4 CameraProjection;
	glm::vec3 CameraPosition;
	glm::vec3 CameraForward;
	glm::vec3 CameraUp;
};


