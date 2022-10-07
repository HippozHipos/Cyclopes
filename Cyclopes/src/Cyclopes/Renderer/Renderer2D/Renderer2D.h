#pragma once

#include "../GraphicsContext.h"
#include "../RenderCommand.h"

#include "Cyclopes/Core/Window.h"


namespace cyc {

	class Renderer2D
	{
	public:
		Renderer2D();

	public:
		void OnInit(GraphicsContext* gfx);
		void OnDestroy();

	private:
		GraphicsContext* gfx = nullptr;
	};

}

