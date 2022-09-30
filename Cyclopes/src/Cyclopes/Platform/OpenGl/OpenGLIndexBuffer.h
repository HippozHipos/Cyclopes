#pragma once

#include <Cyclopes/Core/Base.h>

namespace cyc {

	class OpenGLIndexBuffer
	{
	public:
		OpenGLIndexBuffer();

	public:
		void SetIndices(const Cyc_Vector<int>& indices);
		void Init();
		void Bind();
		void BufferData(bool staticDraw = true);
		void DestroyCPUIndexBuffer();
		void Destroy();

	private:
		Cyc_Scoped<Cyc_Vector<int>> m_IndexBuffer;
		uint32_t m_GlBufferId = 0;
	};

}