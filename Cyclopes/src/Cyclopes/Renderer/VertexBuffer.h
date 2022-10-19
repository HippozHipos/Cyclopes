#pragma once

namespace cyc {

	class VertexBuffer
	{
	public:
		virtual void Init() = 0;
		virtual void Bind() const = 0;
		virtual void BufferData(void* data, long long size, bool staticDraw = true) const = 0;
		virtual void Destroy() = 0;

	protected:
		uint32_t m_GlBufferId = 0;
	};

}