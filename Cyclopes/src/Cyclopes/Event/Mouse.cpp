#include "Cycpch.h"
#include "Mouse.h"

#include "Cyclopes/Core/Log.h"

namespace cyc {
	MouseEvent::MouseEvent(EventType type) :
		Event(EventCategory::MOUSE, type)
	{
	}

	EventCategory MouseEvent::GetCategory() const
	{
		return m_Category;
	}

	EventType MouseEvent::GetType() const
	{
		return m_Type;
	}

	void Mouse::OnMouseMove(int x, int y)
	{
		m_EventBuffer.push(EventType::M_MOVED);
		m_X = x;
		m_Y = y;
	}
	void Mouse::OnLButtonDown()
	{
		m_EventBuffer.push(EventType::M_LBUTTON_DOWN);
		TrimBuffer(m_EventBuffer, s_MaxBufferSize);
		m_LeftButtonDown = true;

		m_LeftButtonClick = false;
		if (!m_LastFrameLClick)
		{
			m_LeftButtonClick = true;
			m_LastFrameLClick = true;
		}
	}

	void Mouse::OnRButtonDown()
	{
		m_EventBuffer.push(EventType::M_RBUTTON_DOWN);
		TrimBuffer(m_EventBuffer, s_MaxBufferSize);
		m_RightButtonDown = true;

		m_RightButtonClick = false;
		if (!m_LastFrameRClick)
		{
			m_RightButtonClick = true;
			m_LastFrameRClick = true;
		}
	}

	void Mouse::OnLButtonUp()
	{
		m_EventBuffer.push(EventType::M_LBUTTON_UP);
		TrimBuffer(m_EventBuffer, s_MaxBufferSize);
		m_LeftButtonDown = false;
		m_LastFrameLClick = false;
	}

	void Mouse::OnRButtonUp()
	{
		m_EventBuffer.push(EventType::M_RBUTTON_UP);
		TrimBuffer(m_EventBuffer, s_MaxBufferSize);
		m_LeftButtonDown = false;
		m_LastFrameRClick = false;
	}

	void Mouse::OnMouseEnter()
	{
		m_InWindow = true;
		m_EventBuffer.push(EventType::M_ENTERED_WINDOW);
		TrimBuffer(m_EventBuffer, s_MaxBufferSize);
	}

	void Mouse::OnMouseLeave()
	{
		m_InWindow = false;
		m_EventBuffer.push(EventType::M_LEFT_WINDOW);
		TrimBuffer(m_EventBuffer, s_MaxBufferSize);
	}

	void Mouse::OnMouseRawInput(int lastx, int lasty)
	{
		 m_RawLastChangex = lastx;
		 m_RawLastChangey = lasty;
	}

	bool Mouse::IsInWindow() const
	{
		return m_InWindow;
	}

	int Mouse::GetX() const
	{
		return m_X;
	}

	int Mouse::GetY() const
	{
		return m_Y;
	}
	int Mouse::GetRawChangeX() const
	{
		if (m_RawLastChangex - m_RawPrevLastChangex == 0)
			return 0;

		m_RawPrevLastChangex = m_RawLastChangex;
		return m_RawLastChangex;
	}
	int Mouse::GetRawChangeY() const
	{
		if (m_RawLastChangey - m_RawPrevLastChangey == 0)
			return 0;

		m_RawPrevLastChangey = m_RawLastChangey;
		return m_RawLastChangey;
	}
	bool Mouse::LeftButtonClicked() const
	{
		return m_LeftButtonClick;
	}

	bool Mouse::RightButtonClicked() const
	{
		return m_RightButtonClick;
	}

	bool Mouse::LeftButtonHeld() const
	{
		return m_LeftButtonDown;
	}

	bool Mouse::RightButtonHeld() const
	{
		return m_RightButtonDown;
	}

	bool Mouse::LeftButtonReleased() const
	{
		return !m_LeftButtonDown;
	}

	bool Mouse::RightButtonReleased() const
	{
		return !m_RightButtonDown;
	}

	bool Mouse::HasEvent() const
	{
		return !m_EventBuffer.empty();
	}

	MouseEvent Mouse::ReadEvent() const
	{
		MouseEvent out = m_EventBuffer.front();
		m_EventBuffer.pop();
		return out;
	}
	void Mouse::TrimBuffer(Cyc_Queue<MouseEvent>& buffer, std::uint32_t maxBufferSize)
	{
		while (buffer.size() > maxBufferSize)
			buffer.pop();
	}
}