#pragma once

namespace cyc {

	class OpenGLVertexArray
	{
	public:
		void Init();
		void Bind();
		void Destroy();

	private:
		uint32_t m_GlBufferId;
	};

}

