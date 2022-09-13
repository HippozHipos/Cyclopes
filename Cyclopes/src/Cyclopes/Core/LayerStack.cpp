#include "Cycpch.h"
#include "LayerStack.h"
#include "Window.h"

#include "Log.h"

#include "Assert.h"

namespace cyc {

	LayerStack::LayerStack(Window* window) :
		m_Window(window)
	{
	}

	void LayerStack::OnAttach(Renderer* renderer)
	{
		this->renderer = renderer;
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnAttach();
		}
	}

	void LayerStack::OnEvent(Event& e)
	{
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (!e.propagate)
			{
				return;
			}
		}
	}

	void LayerStack::OnUpdate()
	{
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnUpdate();
		}
	}

	void LayerStack::OnDetach()
	{
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnDetach();
		}
	}

	void LayerStack::OnImGuiRender()
	{
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnImGuiRender();
		}
	}

	void LayerStack::PushLayer(Layer* layer, int index, bool overlay)
	{
		AssertWindowRegistered(layer, "[LayerStack::PushLayer]");
		layer->SetWindow(m_Window);
		layer->SetRenderer(renderer);
		if (!overlay)
		{
			CYC_CORE_ASSERT(index <= m_NNonOverlays,
				"[LayerStack::PushLayer] [Layer = \"" + layer->GetName() + "\"] Index out of range."
			    " Valid Range = 0 to {0}", m_NNonOverlays);

			m_Layers.emplace(m_Layers.begin() + index, layer);
			m_NNonOverlays++;
		}
		else
		{
			CYC_CORE_ASSERT(index <= m_NOverlays,
				"[LayerStack::PushLayer] [Layer = \"" + layer->GetName() + "\"] Index out of range."
				" Valid Range = 0 to {0}", m_NOverlays);

			m_Layers.emplace(m_Layers.begin() + m_NNonOverlays + index, layer);
			m_NOverlays++;
		}
	}

	void LayerStack::PushFrontLayer(Layer* layer, bool overlay)
	{
		AssertWindowRegistered(layer, "[LayerStack::PushFrontLayer]");
		layer->SetWindow(m_Window);
		layer->SetRenderer(renderer);
		if (!overlay)
		{
			m_Layers.emplace(m_Layers.begin(), layer);
			m_NNonOverlays++;
		}
		else
		{
			m_Layers.emplace(m_Layers.begin() + m_NNonOverlays, layer);
			m_NOverlays++;
		}
	}

	void LayerStack::PushBackLayer(Layer* layer, bool overlay)
	{
		AssertWindowRegistered(layer, "[LayerStack::PushBackLayer]");
		layer->SetWindow(m_Window);
		layer->SetRenderer(renderer);
		if (!overlay)
		{
			m_Layers.emplace(m_Layers.end() - m_NOverlays, layer);
			m_NNonOverlays++;
		}
		else
		{
			m_Layers.emplace_back(layer);
			m_NOverlays++;
		}
	}

	void LayerStack::AssertWindowRegistered(const Layer* layer, const Cyc_String& funcName) const
	{
		CYC_CORE_ASSERT(m_Window->IsRegisreted(),
			funcName +
			" [Layer = \"" + layer->GetName() + "\"]" 
			" Window needs to be registered before using layer system\n"
		    "Hint: Call ResigsterWindow(window to which the layer is to be added) in your application class"
		    " before adding layers to the window.");
	}
}