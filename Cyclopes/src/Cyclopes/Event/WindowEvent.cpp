#include "Cycpch.h"
#include "WindowEvent.h"

namespace cyc {

	WindowEvent::WindowEvent(const EventType& type):
		Event(EventCategory::WINDOW, type)
	{
	}

	EventCategory WindowEvent::GetCategory() const
	{
		return m_Category;
	}

	EventType WindowEvent::GetType() const
	{
		return m_Type;
	}
}