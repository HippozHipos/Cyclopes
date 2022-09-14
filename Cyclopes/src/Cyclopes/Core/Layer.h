#pragma once

#include "Cyclopes/Event/Event.h"

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
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);
		virtual void OnDetach();
		virtual void OnImGuiRender();

		const Cyc_String& GetName() const;

		void SetWindow(Window* win);
		void SetRenderer(Renderer* renderer);

	protected:
		Window* window = nullptr;
		Renderer* renderer = nullptr;

	private:
		Cyc_String m_Name;
	};

}
