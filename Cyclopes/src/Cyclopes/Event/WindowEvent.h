#pragma once

#include "Event.h"

namespace cyc {

	class WindowEvent : public Event
	{
	public:
		WindowEvent(const EventType& type);

	public:
		EventCategory GetCategory() const;
		EventType GetType() const;
	};
}
