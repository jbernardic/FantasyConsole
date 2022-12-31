#include "VertexArray.h"
#include "ErrorHandler.h"
#include <iostream>
#include <glad/glad.h>

VertexArray::VertexArray()
{
	(glGenVertexArrays(1, &m_ID));
}

VertexArray::~VertexArray() {

	lcall(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::Bind() const {
	lcall(glBindVertexArray(m_ID));
}

void VertexArray::UnBind() const {
	lcall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(VertexBuffer& vb, unsigned int index, unsigned int count, unsigned int type, unsigned int stride, unsigned int pointer) {
	Bind();
	vb.Bind();
	if (m_VB != &vb) m_Offset = 0;
	if (pointer != 0) { m_Offset = pointer; }
	if (type == GL_FLOAT) {
		glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(m_Offset *sizeof(float)));
		glEnableVertexAttribArray(index);
		m_VB = &vb;
		
	}
	if (pointer == 0) { m_Offset += count; }

}