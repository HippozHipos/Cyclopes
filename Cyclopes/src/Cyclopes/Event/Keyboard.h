#pragma once

#include "Cyclopes/Core/Base.h"
#include "Event.h"

#include <queue>
#include <bitset>

#ifdef CYC_PLATFORM_WINDOWS
	#include "Cyclopes/Platform/Windows/Win32ToCycKeyBindings.h"
#endif

//TODO: MAKE CLIENT FUNCTION for m_EventBuffer

namespace cyc {
	 
	class KeyEvent : public Event
	{
	public:
		KeyEvent(EventType type);

	public:
		EventCategory GetCategory() const override;
		EventType GetType() const override;
	};

	class Keyboard 
	{

	//win32 interface
	public:
		void OnKeyDown(unsigned char keycode);
		void OnKeyUp(unsigned char keycode);
		void OnChar(unsigned char ch);
		void ClearState();

	//client interface
	public:
		bool KeyIsPressed(Key vk) const;
		void SetAutoRepeat(bool repeat) const;
		bool AutoRepeatIsEnabled() const;
		bool HasEvent() const;
		bool HasChar() const;
		unsigned char ReadChar() const;
		KeyEvent ReadEvent() const;

	private:
		template<class BufferType>
		void TrimBuffer(std::queue<BufferType>& buffer, std::uint32_t maxBufferSize)
		{
			while (buffer.size() > maxBufferSize)
				buffer.pop();
		}

	private:
		mutable bool autoRepeatEnabled = false;

	private:
		static constexpr std::uint32_t s_MaxBufferSize = 32u;
		static constexpr std::uint32_t s_NKeyStates = 256;
		mutable std::bitset<s_NKeyStates> m_KeyStates;
		mutable std::queue<KeyEvent> m_EventBuffer;
		mutable std::queue<char> m_CharBuffer;
	};

}

