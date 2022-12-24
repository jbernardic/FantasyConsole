#pragma once
#include "VertexBuffer.h"
class VertexArray {

public:
	VertexArray();
	~VertexArray();
	void AddBuffer(VertexBuffer& vb, unsigned int layout, unsigned int element_count, unsigned int type, unsigned int element_stride, unsigned int element_offset = 0);
	void Bind() const;
	void UnBind() const;
	 unsigned int GetRendID() const{
		return _rendID;
	}
private:
	unsigned int _rendID;
	unsigned int offset = 0;
	VertexBuffer* object = nullptr;
};
