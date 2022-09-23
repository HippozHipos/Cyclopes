#include "Cycpch.h"
#include "Renderer.h"

#include "Cyclopes/Core/Assert.h"

namespace cyc {

	Renderer::Renderer()
	{
	}

	void Renderer::OnInit(GraphicsContext* gfx)
	{
		this->gfx = gfx;
	}

	void Renderer::OnDestroy()
	{
	}
}