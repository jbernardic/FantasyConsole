#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(unsigned int size);
	~VertexBuffer();

	const void Bind() const;
	const void UnBind() const;
	const void SubData(void* data, size_t size, unsigned int offset=0) const;
	unsigned int  const getRendererID() {
		return _rendID;
	}
private:
	unsigned int _rendID;
};

