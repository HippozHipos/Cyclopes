#include "Cycpch.h"
#include "RendererAPI.h"
#include "Cyclopes/Core/Assert.h"

#include "Cyclopes/Platform/OpenGl/OpenGLRendererAPI.h"

namespace cyc {

	RendererAPI::Type RendererAPI::m_Type;

	Cyc_Scoped<RendererAPI> RendererAPI::Create(RendererAPI::Type type)
	{
		switch ((int)type)
		{
			case (int)RendererAPI::Type::OPENGL: 
			{
				m_Type = type; 
				return Cyc_MakeScoped<OpenGLRendererAPI>();
			}
		}

		CYC_CORE_ASSERT(false, "RendererAPI creation failed. RendererAPI::Type is not valid.");
		return nullptr;
	}

	RendererAPI::Type RendererAPI::GetType()
	{
		return m_Type;
	}
}