#pragma once

namespace Surpass {

	class FullScreenQuad
	{
	public:
		FullScreenQuad();
		~FullScreenQuad();

		void init();

		FullScreenQuad(const FullScreenQuad&) = delete;
		FullScreenQuad& operator=(const FullScreenQuad&) = delete;
		FullScreenQuad(FullScreenQuad&&) = delete;
		FullScreenQuad& operator=(const FullScreenQuad&&) = delete;

		void draw();
	private:
		unsigned int m_Attribute = 0, m_Buffer = 0;
	};

}