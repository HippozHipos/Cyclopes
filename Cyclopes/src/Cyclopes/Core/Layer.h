#pragma once

#include "Cyclopes/Event/Event.h"

namespace cyc {

	class Window;
	class Layer
	{
	public:
		Layer(const std::string& name);
		virtual ~Layer() = default;

	public:
		virtual void OnAttach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;
		virtual void OnDetach() = 0;

		const std::string& GetName() const;
		void SetWindow(Window* win);

	protected:
		Window* m_Window = nullptr;

	private:
		std::string m_Name;
	};

}
