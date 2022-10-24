#pragma once

#include <queue>

#include "Event.h"
#include "Cyclopes/Core/Base.h"

//TODO: Implement mouse scrolls. Implement client function for m_Buffer

namespace cyc {

	class MouseEvent : public Event
	{
	public:
		MouseEvent(EventType type);

	public:
		EventCategory GetCategory() const;
		EventType GetType() const override;
	};

	class Mouse 
	{
	public:
		Mouse() = default;
		virtual ~Mouse() = default;

	//win32 api facing interface
	public:
		void OnMouseMove(int x, int y);
		void OnLButtonDown();
		void OnRButtonDown();
		void OnLButtonUp();
		void OnRButtonUp();
		void OnMouseEnter();
		void OnMouseLeave();

		void OnMouseRawInput(int lastx, int lasty);

		//client facing interface
	public:
		bool IsInWindow() const;
		int GetX() const;
		int GetY() const;
		int GetRawChangeX() const;
		int GetRawChangeY() const;
		bool LeftButtonClicked() const;
		bool RightButtonClicked() const;
		bool LeftButtonHeld() const;
		bool RightButtonHeld() const;
		bool LeftButtonReleased() const;
		bool RightButtonReleased() const;
		bool HasEvent() const;
		MouseEvent ReadEvent() const;

	private:
		void TrimBuffer(Cyc_Queue<MouseEvent>& buffer, std::uint32_t maxBufferSize);

	private:
		static constexpr std::uint32_t s_MaxBufferSize = 32u;
		mutable Cyc_Queue<MouseEvent> m_EventBuffer;

	private:
		bool m_InWindow = false;
		bool m_LeftButtonDown = false;
		bool m_RightButtonDown = false;
		bool m_LastFrameLClick = false;
		bool m_LastFrameRClick = false;
		bool m_LeftButtonClick = false;
		bool m_RightButtonClick = false;

	private:
		int m_X = 0;
		int m_Y = 0;
		int m_RawLastChangex = 0;
		int m_RawLastChangey = 0;
		mutable int m_RawPrevLastChangex = 0;
		mutable int m_RawPrevLastChangey = 0;
	};
}

