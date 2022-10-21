#pragma once

#include "Cyclopes/Core/Base.h"
#include "Cyclopes/Core/Assert.h"


#include "glad/glad.h"

namespace cyc {

	class OpenGLVertexArray
	{
	private:
		enum class LayoutType : std::uint8_t
		{
			INT,
			FLOAT,
			DOUBLE,
			SHORT
		};
		
		struct Layout
		{
			Layout(int index, int size, bool norm, int stride, int offset) :
				index(index), size(size), normalize(norm), stride(stride), offset(offset)
			{
			}
			int index{};
			int size{};
			bool normalize{};
			int stride{};
			int offset{};
			LayoutType type;
		};

	public:
		OpenGLVertexArray();

	public:
		void Use();
		void Init();
		void Bind();
		void EnableAttribute(int i);
		void DisableAttribute(int i);
		void Destroy();

	public:
		template<class Type>
		void AddLayout(int index, int size, bool normalize, int stride, int offset)
		{
			Layout vl = { index, size, normalize, stride, offset };
			AddLayoutHelper<Type>(vl);
		}

		void DestroyVertexLayout()
		{
			m_LayoutBuffer.reset();
		}

	private:
		template<class Type>
		void AddLayoutHelper(Layout& vl)
		{
			CYC_CORE_ASSERT(false, "Vertex Data of type \"{0}\" is not allowed.", typeid(DataType).name());
		}

		template<> void AddLayoutHelper<int>(Layout& vl)
		{
			vl.type = LayoutType::INT;
			m_LayoutBuffer->push_back(vl);
		}

		template<> void AddLayoutHelper<float>(Layout& vl)
		{
			vl.type = LayoutType::FLOAT;
			m_LayoutBuffer->push_back(vl);
		}

		template<> void AddLayoutHelper<double>(Layout& vl)
		{
			vl.type = LayoutType::DOUBLE;
			m_LayoutBuffer->push_back(vl);
		}

		template<> void AddLayoutHelper<short>(Layout& vl)
		{
			vl.type = LayoutType::SHORT;
			m_LayoutBuffer->push_back(vl);
		}

	private:
		uint32_t m_GlBufferId;
		Cyc_Scoped<Cyc_Vector<Layout>> m_LayoutBuffer;
	};

}

