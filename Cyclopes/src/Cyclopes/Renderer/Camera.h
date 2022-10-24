#pragma once

#include <glm/glm.hpp>

#include "Cyclopes/Event/Keyboard.h"
#include "Cyclopes/Event/Mouse.h"

namespace cyc {

	class Camera
	{
	public:
		glm::vec3 Transform { 0.0f, 0.0f, 0.0f};
		glm::vec3 WorldUp { 0.0f, 1.0f, 0.0f };

		float Yaw = -90.0f;
		float Pitch = 0.0f;

		bool ConstrainPitch = true;

	public:
		const glm::vec3& Forward() const;
		const glm::vec3& Backward() const;
		const glm::vec3& Right() const;
		const glm::vec3& Left() const;
		const glm::vec3& Up() const;
		const glm::vec3& Down() const;

	public:
		glm::mat4 MakeViewMatrix() const;

	public:
		void Update();

	private:
		glm::vec3 forward{};
		glm::vec3 right{};
		glm::vec3 up{};
	};

	class PerspectiveCamera : public Camera
	{
	public:
		float Fov = glm::radians(45.0f);
		float AspectRatio = 1.0f;
		float NearPlane = 0.1f;
		float FarPlane = 100.0f;

		float MovementSensitivity = 1.0f;

	public:
		void RotateWithMouse(const cyc::Mouse& mouse);
		void MoveWithKeyboard(const cyc::Keyboard& keyboard);

		void SetRotationSensitivity(float val);

	public:
		glm::mat4 MakeProjectionMatrix();

	private:
		float m_SmoothMouseChangeX = 0;
		float m_SmoothMouseChangeY = 0;

	private:
		static constexpr float m_MinRotationSens = 0.0f;
		static constexpr float m_MaxRotationSens = 10.0f;
		float m_RotationSensitivity = 3.0f;
	};

}
