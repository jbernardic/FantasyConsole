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
		return m_ID;
	}
private:
	unsigned int m_ID;
	unsigned int m_Offset = 0;
	VertexBuffer* m_VB = nullptr;
};
