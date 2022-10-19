#pragma once

#include "GraphicsContext.h"
#include "RenderCommand.h"

#include "Cyclopes/Core/Window.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>


namespace cyc {

	class Renderer2D
	{
	public:
		Renderer2D();

	public:
		void Init(GraphicsContext* gfx);
		void Destroy();

	public:
		void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color);

	private:
		GraphicsContext* gfx = nullptr;
	};

}

