#include "IndexBuffer.h"
#include <glad/glad.h>
#include "Renderer.h"
#include <array>


IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
{
	(glGenBuffers(1, &_rendID));
	lcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendID));
	lcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	std::cout << "IndexBuffer DTOR" <<std::endl;
	if(_rendID > 0) lcall(glDeleteBuffers(1, &_rendID));
}

void IndexBuffer::Bind() const {
	lcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendID));
}

void IndexBuffer::UnBind() const {
	lcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
