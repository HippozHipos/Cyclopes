#pragma once

#include "Cyclopes/Core/Base.h"
#include <queue>

namespace cyc {

	enum class EventCategory
	{
		KEYBOARD,
		MOUSE,
		WINDOW,
	};

	//K_ = Keyboard event, M_ = Mouse event, W_ = Window event 
	enum class EventType
	{
		K_PRESSED, K_RELEASED,

		M_LBUTTON_DOWN, M_RBUTTON_DOWN, M_LBUTTON_UP, M_RBUTTON_UP, M_WHEEL_SCROLL_UP,
		M_WHEEL_SCROLL_DOWN, M_ENTERED_WINDOW, M_LEFT_WINDOW, M_MOVED,

		W_RESIZED, W_FOCUSED, W_FOCUS_KILLED, W_MOVED, W_CLOSE
	};

	class Event
	{
	public:
		Event(EventCategory category, EventType type);
		virtual ~Event() = default;

	public:
		virtual EventCategory GetCategory() const = 0;
		virtual EventType GetType() const = 0;

	public:
		bool propagate = false;

	protected:
		EventType m_Type;
		EventCategory m_Category;
	};
}

