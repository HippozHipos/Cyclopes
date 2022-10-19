#pragma once

#include "Cyclopes/Renderer/VertexBuffer.h"

#include "Cyclopes/Core/Base.h"
#include "Cyclopes/Core/Assert.h"
#include "OpenGLError.h"

#include <vector>
#include <glad/glad.h>


namespace cyc {

	//class OpenGLVertexBuffer : public VertexBuffer
	//{
	//public:
	//	OpenGLVertexBuffer()
	//	{
	//		m_VertexBuffer = Cyc_MakeScoped<Cyc_Vector<std::uint8_t>>();
	//	}

	//public:
	//	void Init()
	//	{
	//		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Init]");

	//		glGenBuffers(1, &m_GlBufferId);
	//	}

	//	template<class Type>
	//	void SetVertices(const std::vector<Type>& vertices)
	//	{
	//		m_VertexBuffer->resize(vertices.size() * sizeof(Type));
	//		std::memcpy(m_VertexBuffer->data(), vertices.data(), vertices.size() * sizeof(Type));
	//	}

	//	void BufferData(bool staticDraw = true) const
	//	{
	//		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::BufferData]");
	//		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_VertexBuffer->size(), m_VertexBuffer->data(), staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

	//	}

	//	void Bind() const
	//	{
	//		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Bind]");

	//		glBindBuffer(GL_ARRAY_BUFFER, m_GlBufferId);
	//	}

	//public:
	//	void DestroyCPUVertexBuffer()
	//	{
	//		m_VertexBuffer.reset();
	//	}

	//	void Destroy()
	//	{
	//		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Destroy]");

	//		glDeleteBuffers(1, &m_GlBufferId);
	//		m_VertexBuffer.reset();
	//	}

	//private:
	//	Cyc_Scoped<Cyc_Vector<std::uint8_t>> m_VertexBuffer;
	//	uint32_t m_GlBufferId = 0;
	//};

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void Init() override;
		void Bind() const override;
		void BufferData(void* data, long long int size, bool staticDraw = true) const override;
		void Destroy() override;
	};

}

