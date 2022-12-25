#pragma once
class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	IndexBuffer() {};
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_ID = 0;
};

