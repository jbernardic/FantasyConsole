#pragma once
#include "Sprite.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <unordered_map>

#define MaxSpriteCount 65536

class SpriteBatch{
public:
	SpriteBatch();
	void Draw(Sprite& sprite);
	void End();
	void Begin();
	static unsigned int Instance;
private:
	size_t m_BufferSize = 0;
	Shader* m_Shader;
	std::unique_ptr<IndexBuffer> m_IB;
	VertexArray m_VA;
	VertexBuffer m_VB = VertexBuffer(MaxSpriteCount*sizeof(Vertex)*4);
	std::unordered_map<void*, unsigned int> m_Textures;
};
