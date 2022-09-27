#pragma once

#include "Cyclopes/Core/Base.h"

#include <vector>
#include <glad/glad.h>

namespace cyc {

	struct VertexLayout
	{
		VertexLayout(int index, int size, bool norm, int stride, int offset);
		int index{};
		int size{};
		bool normalize{};
		int stride{};
		int offset{};
	};

	template<class Type>
	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer()
		{
			m_VertexBuffer = Cyc_MakeScoped<Cyc_Vector<Type>>();
			m_VertexLayout = Cyc_MakeScoped<Cyc_Vector<VertexLayout>>();
		}

	public:
		void Init()
		{
			glGenBuffers(1, &m_GlBufferId);
		}

		void SetVertices(const std::vector<Type>& vertices)
		{
			*m_VertexBuffer = vertices;
		}

		void BufferData(bool staticDraw = true) const
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(Type) * m_VertexBuffer->size(), m_VertexBuffer->data(), staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		}

		void Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_GlBufferId);
		}

		void AddLayout(const VertexLayout& vl)
		{
			m_VertexLayout->push_back(vl);
			AddLayoutHelper<Type>(vl);
			glEnableVertexAttribArray(m_VertexLayout.size() - 1);
		}

		void AddLayout(int index, int size, bool normalize, int stride, int offset)
		{
			m_VertexLayout->emplace_back(index, size, normalize, stride, offset);
			AddLayoutHelper<Type>({index, size, normalize, stride, offset});
			glEnableVertexAttribArray(m_VertexLayout->size() - 1);
		}

	public:
		void DestroyVertexBuffer()
		{
			m_VertexBuffer.reset();
		}

		void DestroyVertexLayout()
		{
			m_VertexLayout.reset();
		}

		void Destroy()
		{
			glDeleteBuffers(1, &m_GlBufferId);
			m_VertexBuffer.reset();
			m_VertexLayout.reset();
		}

	private:
		template<class DataType>
		void AddLayoutHelper(const VertexLayout& vl)
		{
			CYC_CORE_ASSERT(false, "Vertex Data of type \"{0}\" is not allowed.", typeid(DataType).name());
		}

		template<> void AddLayoutHelper<int>(const VertexLayout& vl)
		{
			glVertexAttribPointer(vl.index, vl.size, GL_INT, vl.normalize, vl.stride, (void*)vl.offset);
		}

		template<> void AddLayoutHelper<float>(const VertexLayout& vl)
		{
			glVertexAttribPointer(vl.index, vl.size, GL_FLOAT, vl.normalize, vl.stride, (void*)vl.offset);
		}

		template<> void AddLayoutHelper<double>(const VertexLayout& vl)
		{
			glVertexAttribPointer(vl.index, vl.size, GL_DOUBLE, vl.normalize, vl.stride, (void*)vl.offset);
		}

		template<> void AddLayoutHelper<short>(const VertexLayout& vl)
		{
			glVertexAttribPointer(vl.index, vl.size, GL_SHORT, vl.normalize, vl.stride, (void*)vl.offset);
		}

	private:
		Cyc_Scoped<Cyc_Vector<VertexLayout>> m_VertexLayout;
		Cyc_Scoped<Cyc_Vector<Type>> m_VertexBuffer;
		uint32_t m_GlBufferId = 0;
	};

}

