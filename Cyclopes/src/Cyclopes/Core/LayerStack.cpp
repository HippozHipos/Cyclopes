#include "Cycpch.h"
#include "LayerStack.h"
#include "Window.h"

#include "Log.h"

#include "Assert.h"

namespace cyc {

	LayerStack::LayerStack(Window* window) :
		window(window)
	{
	}

	void LayerStack::_OnAttach(Renderer2D* r2d, GraphicsContext* gfx)
	{
		this->renderer2D = r2d;
		this->gfx = gfx;
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnAttach();
		}
	}

	void LayerStack::_OnEvent(Event& e)
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

	void LayerStack::_OnUpdate()
	{
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnUpdate();
		}
	}

	void LayerStack::_OnDetach()
	{
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnDetach();
		}
	}

	void LayerStack::_OnImGuiRender()
	{
		for (auto& it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->OnImGuiRender();
		}
	}

	void LayerStack::PushLayer(Layer* layer, int index, bool overlay)
	{
		layer->SetWindow(window);
		layer->SetRenderer(renderer2D);
		layer->SetGfx(gfx);
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
		layer->SetWindow(window);
		layer->SetRenderer(renderer2D);
		layer->SetGfx(gfx);
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
		layer->SetWindow(window);
		layer->SetRenderer(renderer2D);
		layer->SetGfx(gfx);
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
}