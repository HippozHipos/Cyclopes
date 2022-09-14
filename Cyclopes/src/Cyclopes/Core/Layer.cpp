#include "Cycpch.h"
#include "Layer.h"

namespace cyc {

	Layer::Layer(const Cyc_String& name):
		m_Name(name)
	{
	}

	void Layer::OnAttach() {}
	void Layer::OnUpdate() {}
	void Layer::OnEvent(Event& e) { e.propagate = true; }
	void Layer::OnDetach() {}
	void Layer::OnImGuiRender() {}

	const Cyc_String& Layer::GetName() const
	{
		return m_Name;
	}

	void Layer::SetWindow(Window* win)
	{
		window = win;
	}

	void Layer::SetRenderer(Renderer* renderer)
	{
		this->renderer = renderer;
	}

}
