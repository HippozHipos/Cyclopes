#pragma once

#include "Cyclopes/Event/Event.h"

namespace cyc {

	class Window;
	class Layer
	{
	public:
		Layer(const Cyc_String& name);
		virtual ~Layer() = default;

	public:
		virtual void OnAttach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;
		virtual void OnDetach() = 0;

		const Cyc_String& GetName() const;
		void SetWindow(Window* win);

	protected:
		Window* m_Window = nullptr;

	private:
		Cyc_String m_Name;
	};

}
