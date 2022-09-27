#include "Cycpch.h"
#include "OpenGLVertexBuffer.h"

namespace cyc {

	VertexLayout::VertexLayout(int index, int size, bool norm, int stride, int offset) :
		index(index), size(size), normalize(norm), stride(stride), offset(offset)
	{
	}
}