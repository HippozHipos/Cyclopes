#include "Cycpch.h"
#include "Layer.h"

namespace cyc {

	Layer::Layer(const std::string& name):
		m_Name(name)
	{
	}

	const std::string& Layer::GetName() const
	{
		return m_Name;
	}

	void Layer::SetWindow(Window* win)
	{
		m_Window = win;
	}

}
