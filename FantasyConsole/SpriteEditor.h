#pragma once
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <iostream>
class SpriteEditor
{
public:
	SpriteEditor(unsigned int spriteSize);
	void Draw();
private:
	VertexArray m_VA;
	std::unique_ptr<VertexBuffer> m_VB;
	std::unique_ptr<IndexBuffer> m_IB;
};

