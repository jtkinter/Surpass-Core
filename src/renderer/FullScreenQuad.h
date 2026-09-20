#pragma once

namespace Surpass {

	class FullScreenQuad
	{
	public:
		FullScreenQuad();
		~FullScreenQuad();

		FullScreenQuad(const FullScreenQuad&) = delete;
		FullScreenQuad& operator=(const FullScreenQuad&) = delete;
		FullScreenQuad(const FullScreenQuad&&) = delete;
		FullScreenQuad&& operator=(const FullScreenQuad&&) = delete;

		void draw();
	private:
		unsigned int m_Attribute, m_Buffer;
	};

}