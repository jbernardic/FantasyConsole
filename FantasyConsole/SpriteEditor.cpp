#include "SpriteEditor.h"

SpriteEditor::SpriteEditor(unsigned int spriteSize)
{
	unsigned int* indices = new unsigned int[6 * spriteSize];
	unsigned int offset = 0;
	for (int i = 0; i < 6* spriteSize; i += 6) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;
		offset += 4;
	}
	m_IB = std::make_unique<IndexBuffer>(indices,  6*spriteSize);
}

void SpriteEditor::Draw()
{

}
