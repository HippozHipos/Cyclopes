#include "Cycpch.h"
#include "Layer.h"

namespace cyc {

	Layer::Layer(const Cyc_String& name):
		m_Name(name)
	{
	}

	const Cyc_String& Layer::GetName() const
	{
		return m_Name;
	}

	void Layer::SetWindow(Window* win)
	{
		m_Window = win;
	}

}
