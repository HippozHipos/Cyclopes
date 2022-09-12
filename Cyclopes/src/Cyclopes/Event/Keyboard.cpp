#include "Cycpch.h"
#include "Keyboard.h"

namespace cyc {
	KeyEvent::KeyEvent(EventType type) :
		Event(EventCategory::KEYBOARD, type)
	{
	}

	EventCategory KeyEvent::GetCategory() const
	{
		return m_Category;
	}

	EventType KeyEvent::GetType() const
	{
		return m_Type;
	}

	void Keyboard::OnKeyDown(unsigned char keycode)
	{
		m_KeyStates[keycode] = true;
		m_EventBuffer.push(KeyEvent(EventType::K_PRESSED));
		TrimBuffer(m_EventBuffer, s_MaxBufferSize);
	}

	void Keyboard::OnKeyUp(unsigned char keycode)
	{
		m_KeyStates[keycode] = false;
		m_EventBuffer.push(KeyEvent(EventType::K_RELEASED));
		TrimBuffer(m_EventBuffer, s_MaxBufferSize);
	}

	void Keyboard::OnChar(unsigned char ch)
	{
		m_CharBuffer.push(ch);
		TrimBuffer(m_CharBuffer, s_MaxBufferSize);
	}

	void Keyboard::ClearState()
	{
		m_KeyStates.reset();
	}

	bool Keyboard::KeyIsPressed(Key vk) const
	{
		return m_KeyStates[(uint32_t)vk];
	}

	void Keyboard::SetAutoRepeat(bool repeat) const
	{
		autoRepeatEnabled = repeat;
	}

	bool Keyboard::AutoRepeatIsEnabled() const
	{
		return autoRepeatEnabled;
	}

	bool Keyboard::HasEvent() const
	{
		return !m_EventBuffer.empty();
	}

	bool Keyboard::HasChar() const
	{
		return !m_CharBuffer.empty();
	}

	unsigned char Keyboard::ReadChar() const
	{
		unsigned char out = m_CharBuffer.front();
		m_CharBuffer.pop();
		return out;
	}

	KeyEvent Keyboard::ReadEvent() const
	{
		KeyEvent out = m_EventBuffer.front();
		m_EventBuffer.pop();
		return out;
	}
}
