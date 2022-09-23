#pragma once

#include "Cyclopes/Event/Event.h"
#include "Cyclopes/Renderer/GraphicsContext.h"

namespace cyc {

	class Window;
	class Renderer;
	class Layer
	{
	public:
		Layer(const Cyc_String& name);
		virtual ~Layer() = default;

	public:
		virtual void OnAttach();
		virtual void OnUpdate(float elapsedTime);
		virtual void OnEvent(Event& e);
		virtual void OnDetach();
		virtual void OnImGuiRender();

		const Cyc_String& GetName() const;

		void SetWindow(Window* win);
		void SetRenderer(Renderer* renderer);
		void Layer::SetGfx(GraphicsContext* gfx);

	protected:
		Window* window = nullptr;
		Renderer* renderer = nullptr;
		GraphicsContext* gfx = nullptr;

	private:
		Cyc_String m_Name;
	};

}
