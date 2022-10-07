#include "Cycpch.h"
#include "Renderer2D.h"

#include "Cyclopes/Core/Assert.h"

namespace cyc {

	Renderer2D::Renderer2D()
	{
	}

	void Renderer2D::Init(GraphicsContext* gfx)
	{
		this->gfx = gfx;
	}

	void Renderer2D::Destroy()
	{
	}
}