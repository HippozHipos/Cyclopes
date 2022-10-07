#pragma once

#include "Cyclopes/Event/Event.h"
#include "Cyclopes/Renderer/GraphicsContext.h"

namespace cyc {

	class Window;
	class Renderer2D;
	class Layer
	{
	public:
		Layer(const Cyc_String& name);
		virtual ~Layer() = default;

	public:
		virtual void OnAttach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);
		virtual void OnDetach();
		virtual void OnImGuiRender();

		const Cyc_String& GetName() const;

		void SetWindow(Window* win);
		void SetRenderer(Renderer2D* renderer);
		void Layer::SetGfx(GraphicsContext* gfx);

	protected:
		Window* window = nullptr;
		Renderer2D* renderer2D = nullptr;
		GraphicsContext* gfx = nullptr;

	private:
		Cyc_String m_Name;
	};

}
