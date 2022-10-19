#pragma once

namespace cyc {

	class IndexBuffer
	{
	public:
		virtual void Init(std::uint32_t count) = 0;
		virtual void Bind() const = 0;
		virtual void BufferData(void* data, long long size, bool staticDraw = true) const = 0;
		virtual void Destroy() = 0;	
		std::uint32_t GetCount() const;
	
	protected:
		std::uint32_t m_GlBufferId = 0;
		std::uint32_t m_Count = 0;
	};

}
