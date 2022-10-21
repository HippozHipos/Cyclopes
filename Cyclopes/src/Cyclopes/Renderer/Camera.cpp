#include "Cycpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <glad/glad.h>

namespace cyc {

	const glm::vec3& Camera::Forward() const
	{
		return forward;
	}

	const glm::vec3& Camera::Right() const
	{
		return right;
	}

	const glm::vec3& Camera::Left() const
	{
		return right * -1.0f;
	}

	const glm::vec3& Camera::Up() const
	{
		return up;
	}

	const glm::vec3& Camera::Down() const
	{
		return up * -1.0f;
	}

	glm::mat4 Camera::MakeViewMatrix() const
	{
		return glm::lookAt(Transform, Transform + forward, up);
	}

	void Camera::Update()
	{
		glm::vec3 rawfront;
		rawfront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		rawfront.y = sin(glm::radians(Pitch));
		rawfront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

		forward = glm::normalize(rawfront);
		right = glm::normalize(glm::cross(forward, WorldUp));
		up = glm::normalize(glm::cross(right, forward));

		if (ConstrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}
	}

	glm::mat4 PerspectiveCamera::MakeProjectionMatrix()
	{
		return glm::perspective(Fov, AspectRatio, NearPlane, FarPlane);
	}
}
