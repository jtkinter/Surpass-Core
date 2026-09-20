#include "sppch.h"
#include "FullScreenQuad.h"

namespace Surpass {

	FullScreenQuad::FullScreenQuad()
	{
		float vertices[] = {
			-1.0f,-1.0f, 0.0f, 0.0f,
			 1.0f,-1.0f, 1.0f, 0.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f,-1.0f, 0.0f, 0.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 1.0f
		};

		glGenVertexArrays(1, &m_Attribute);
		glBindVertexArray(m_Attribute);

		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		int sz = sizeof(float);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sz, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sz, (void*)(2 * sz));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	FullScreenQuad::~FullScreenQuad()
	{
		glDeleteVertexArrays(1, &m_Attribute);
		glDeleteBuffers(1, &m_Buffer);
	}

	void FullScreenQuad::draw()
	{
		glBindVertexArray(m_Attribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}