#include "IndexBuffer.h"
#include <glad/glad.h>
#include "ErrorHandler.h"
#include <iostream>
#include <array>


IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
{
	(glGenBuffers(1, &m_ID));
	lcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	lcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	lcall(glDeleteBuffers(1, &m_ID));
}

void IndexBuffer::Bind() const {
	lcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::UnBind() const {
	lcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
