#include "Cycpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <glad/glad.h>

#include <Cyclopes/Core/Time.h>

#include <glm/gtx/compatibility.hpp>

namespace cyc {

	const glm::vec3& Camera::Forward() const { return forward; }
	const glm::vec3& Camera::Backward() const{ return forward * -1.0f; }
	const glm::vec3& Camera::Right() const { return right; }
	const glm::vec3& Camera::Left() const { return right * -1.0f; }
	const glm::vec3& Camera::Up() const { return up; }
	const glm::vec3& Camera::Down() const{ return up * -1.0f; }

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

	void PerspectiveCamera::RotateWithMouse(const cyc::Mouse& mouse)
	{
		float mcx = (float)mouse.GetRawChangeX();
		float mcy = (float)mouse.GetRawChangeY();

		Yaw += m_SmoothMouseChangeX;
		Pitch += -m_SmoothMouseChangeY;
		
		m_SmoothMouseChangeX = (mcx - m_SmoothMouseChangeX) * Time::GetDeltaTime() * m_RotationSensitivity;
		m_SmoothMouseChangeY = (mcy - m_SmoothMouseChangeY) * Time::GetDeltaTime() * m_RotationSensitivity;
	}

	void PerspectiveCamera::MoveWithKeyboard(const cyc::Keyboard& keyboard)
	{
		if (keyboard.KeyIsPressed(cyc::Key::Q))
			Transform += Forward()	* cyc::Time::GetDeltaTime() * MovementSensitivity;
		if (keyboard.KeyIsPressed(cyc::Key::E))
			Transform += Backward() * cyc::Time::GetDeltaTime() * MovementSensitivity;
		if (keyboard.KeyIsPressed(cyc::Key::D))
			Transform += Right()	* cyc::Time::GetDeltaTime() * MovementSensitivity;
		if (keyboard.KeyIsPressed(cyc::Key::A))
			Transform += Left()		* cyc::Time::GetDeltaTime() * MovementSensitivity;
		if (keyboard.KeyIsPressed(cyc::Key::W))
			Transform += Up()		* cyc::Time::GetDeltaTime() * MovementSensitivity;
		if (keyboard.KeyIsPressed(cyc::Key::S))
			Transform += Down()		* cyc::Time::GetDeltaTime() * MovementSensitivity;
	}

	void PerspectiveCamera::SetRotationSensitivity(float val)
	{
		float sens = glm::clamp(val, m_MinRotationSens, m_MaxRotationSens) / m_MaxRotationSens;
		float actualSensMax = 1000.0f;
		m_RotationSensitivity = sens * actualSensMax;
	}

	glm::mat4 PerspectiveCamera::MakeProjectionMatrix()
	{
		return glm::perspective(Fov, AspectRatio, NearPlane, FarPlane);
	}
}
