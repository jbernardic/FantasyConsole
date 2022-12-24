#include "VertexBuffer.h"
#include <glad/glad.h>
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	lcall(glGenBuffers(1, &_rendID));
	lcall(glBindBuffer(GL_ARRAY_BUFFER, _rendID));
	lcall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::VertexBuffer(unsigned int size) {
	lcall(glGenBuffers(1, &_rendID));
	lcall(glBindBuffer(GL_ARRAY_BUFFER, _rendID));
	lcall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
}
VertexBuffer::~VertexBuffer() {
	std::cout << "VertexBuffer dtor"<<std::endl;
	lcall(glDeleteBuffers(1, &_rendID));
}

const void VertexBuffer::Bind() const {
	lcall(glBindBuffer(GL_ARRAY_BUFFER, _rendID));
}

const void VertexBuffer::UnBind() const {
	lcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

const void VertexBuffer::SubData(void* data, size_t size, unsigned int offset) const {
	lcall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data))
}