#pragma once

#include "GraphicsContext.h"
#include "Cyclopes/Core/Window.h"

#include "RenderCommands.h"

namespace cyc {

	class Renderer
	{
	public:
		Renderer();

	public:
		void OnInit(GraphicsContext* gfx);
		void OnDestroy();

	private:
		GraphicsContext* gfx = nullptr;
	};

}

