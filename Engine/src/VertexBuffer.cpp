#include "VertexBuffer.h"
#include "ErrorHandler.h"
#include <glad/glad.h>
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	lcall(glGenBuffers(1, &m_ID));
	lcall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	lcall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::VertexBuffer(unsigned int size) {
	lcall(glGenBuffers(1, &m_ID));
	lcall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	lcall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
}
VertexBuffer::~VertexBuffer() {
	lcall(glDeleteBuffers(1, &m_ID));
}

const void VertexBuffer::Bind() const {
	lcall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

const void VertexBuffer::UnBind() const {
	lcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

const void VertexBuffer::SubData(void* data, size_t size, unsigned int offset) const {
lcall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data))
}
