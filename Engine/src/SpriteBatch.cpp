#include <array>
#include "SpriteBatch.h"

unsigned int SpriteBatch::Instance = 0;

SpriteBatch::SpriteBatch() {
	unsigned int* indices = new unsigned int[MaxSpriteCount * 6];
	unsigned int offset = 0;
	for (int i = 0; i < MaxSpriteCount*6; i+=6) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;
		offset += 4;
	}

	m_IB = std::make_unique<IndexBuffer>(indices, MaxSpriteCount * 6);
	delete[] indices;

	m_VA.AddBuffer(m_VB, 0, 2, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, Position) / sizeof(float));
	m_VA.AddBuffer(m_VB, 1, 4, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, Color) / sizeof(float));
	m_VA.AddBuffer(m_VB, 2, 2, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, TexCoord) / sizeof(float));
	m_VA.AddBuffer(m_VB, 3, 1, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, TexIndex) / sizeof(float));
	m_VA.AddBuffer(m_VB, 4, 1, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, IsBitmap) / sizeof(float));
	m_IB->Bind();

	rm::LoadShader("Resources/Sprite.Shader", "sprite" + std::to_string(Instance));
	m_Shader = &rm::GetShader("sprite" + std::to_string(Instance));

	glm::mat4 model = glm::mat4(1.0f);
	m_Shader->SetMatrix4("model", model);
	int samplers[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	m_Shader->SetIntArray("textures", samplers, 32);

	Instance++;
}

void SpriteBatch::Draw(Sprite& sprite) 
{
	unsigned int texIndex;
	if (m_Textures.find(sprite.Texture) != m_Textures.end()) {
		texIndex = m_Textures[sprite.Texture];
	}
	else {
		texIndex = m_Textures.size();
	}

	auto dataArray = sprite.GetVertices(static_cast<float>(texIndex));
	m_VB.Bind();
	m_VB.SubData(dataArray.data(), dataArray.size() * sizeof(Vertex), static_cast<unsigned int>(m_BufferSize));
	sprite.Texture->Bind(texIndex);
	m_BufferSize += dataArray.size() * sizeof(Vertex);
	m_Textures[sprite.Texture] = texIndex;
}

void SpriteBatch::End() {
	m_Shader->Bind();
	m_VA.Bind();
	m_IB->Bind();
	lcall(glDrawElements(GL_TRIANGLES, m_BufferSize/(4*sizeof(Vertex))*6, GL_UNSIGNED_INT, nullptr));
	m_BufferSize = 0;
	m_Textures.clear();
}

void SpriteBatch::Begin() {
	m_BufferSize = 0;
	m_Textures.clear();
}
