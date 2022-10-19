#pragma once

#include "Cyclopes/Renderer/IndexBuffer.h"

#include "Cyclopes/Core/Base.h"

namespace cyc {

	//class OpenGLIndexBuffer : public IndexBuffer
	//{
	//public:
	//	OpenGLIndexBuffer();

	//public:
	//	void SetIndices(const Cyc_Vector<int>& indices);
	//	void Init();
	//	void Bind();
	//	void BufferData(bool staticDraw = true);
	//	void DestroyCPUIndexBuffer();
	//	void Destroy();

	//private:
	//	Cyc_Scoped<Cyc_Vector<int>> m_IndexBuffer;
	//	uint32_t m_GlBufferId = 0;
	//};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		void Init();
		void Bind();
		void BufferData(void* data, long long int size, bool staticDraw = true);
		void Destroy();

	private:
		uint32_t m_GlBufferId = 0;
	};

}