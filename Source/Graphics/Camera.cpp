#include "Graphics/Camera.h"
#include "Framework/Input.h"

Camera::Camera(int windowWidth, int windowHeight)
{
	UpdateViewMatrix();
	ResizeProjectionMatrix(windowWidth, windowHeight);
}

Camera::Camera(glm::vec3 position, int windowWidth, int windowHeight) : Position(position)
{
	UpdateViewMatrix();
	ResizeProjectionMatrix(windowWidth, windowHeight);
}

void Camera::Update(float deltaTime)
{
	// Simple movement for testing purposes
	float movement = speed * deltaTime;
	if(Input::GetKey(KeyCode::Shift))
	{
		movement *= speedMultiplier;
	}

	if(Input::GetKey(KeyCode::Ctrl))
	{
		movement /= speed;
	}

	int right = Input::GetKey(KeyCode::D) - Input::GetKey(KeyCode::A);
	int up = Input::GetKey(KeyCode::S) - Input::GetKey(KeyCode::W);

	Position.x += right * movement;
	Position.z += up * movement;

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	view = glm::lookAt(Position, Position + front, up);
	viewProjection = projection * view;
}

void Camera::ResizeProjectionMatrix(int windowWidth, int windowHeight)
{
	aspectRatio = float(windowWidth) / float(windowHeight);
	projection = glm::perspective(glm::radians(FOV), aspectRatio, nearClip, farClip);

	viewProjection = projection * view;
}

float Camera::GetFOV()
{
	return FOV;
}

const glm::vec3& Camera::GetForwardVector()
{
	return front;
}

const glm::vec3& Camera::GetUpwardVector()
{
	return up;
}

const glm::mat4& Camera::GetViewProjectionMatrix()
{
	return viewProjection;
}

const glm::mat4& Camera::GetViewMatrix()
{
	return view;
}

const glm::mat4& Camera::GetProjectionMatrix()
{
	return projection;
}