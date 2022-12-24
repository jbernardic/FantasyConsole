#include "SpriteBatch.h"
#include "ResourceManager.h"
#include <array>

unsigned int SpriteBatch::instance = 0;
unsigned int Sprite::instance = 0;

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

	ib = std::make_unique<IndexBuffer>(indices, MaxSpriteCount * 6);
	delete[] indices;

	va.AddBuffer(vb, 0, 2, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, Position) / sizeof(float));
	va.AddBuffer(vb, 1, 4, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, Color) / sizeof(float));
	va.AddBuffer(vb, 2, 2, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, TexCoord) / sizeof(float));
	va.AddBuffer(vb, 3, 1, GL_FLOAT, sizeof(Vertex) / sizeof(float), offsetof(Vertex, TexIndex) / sizeof(float));
	ib->Bind();

	rm::LoadShader("Resources/Sprite.shader", "sprite" + std::to_string(instance));
	shader = &rm::GetShader("sprite" + std::to_string(instance));

	glm::mat4 model = glm::mat4(1.0f);
	shader->SetMatrix4("model", model);
	int samplers[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	shader->SetIntArray("textures", samplers, 32);

	instance++;
}

void SpriteBatch::Draw(Sprite& sprite)
{
	unsigned int texIndex = static_cast<unsigned int>(verticies_size / (4 * sizeof(Vertex)));
	sprite.SetTexIndex(texIndex);
	auto dataArray = sprite.GetVertices();
	vb.Bind();
	vb.SubData(dataArray.data(), dataArray.size() * sizeof(Vertex), static_cast<unsigned int>(verticies_size));
	sprite.GetTexture().Bind(texIndex);
	verticies_size += dataArray.size() * sizeof(Vertex);
}

void SpriteBatch::End() {
	shader->Bind();
	va.Bind();
	lcall(glDrawElements(GL_TRIANGLES, verticies_size/(4*sizeof(Vertex))*6, GL_UNSIGNED_INT, nullptr));
	verticies_size = 0;
}

void SpriteBatch::Start() {
	verticies_size = 0;
}

Sprite::Sprite(const char* path, glm::vec2 position, glm::vec2 size, glm::vec4 color) : m_Position(position), m_Size(size), m_Color(color) {
	rm::LoadTexture(path, "Sprite" + instance);
	m_Texture = &rm::GetTexture("Sprite" + instance);
	instance++;
}

std::array<Vertex, 4> Sprite::GetVertices() {
	//position
	float x = m_Position.x;
	float y = m_Position.y;
	float width = m_Size.x;
	float height = m_Size.y;

	Vertex v0{};
	v0.Position = { x, y+height, };
	v0.Color = m_Color;
	v0.TexCoord = m_TexCoord[0];
	v0.TexIndex = m_TexIndex;
	Vertex v1{};
	v1.Position = { x+width, y+height, };
	v1.Color = m_Color;
	v1.TexCoord = m_TexCoord[1];
	v1.TexIndex = m_TexIndex;
	Vertex v2{};
	v2.Position = { x+width, y, };
	v2.Color = m_Color;
	v2.TexCoord = m_TexCoord[2];
	v2.TexIndex = m_TexIndex;
	Vertex v3{};
	v3.Position = { x, y, };
	v3.Color = m_Color;
	v3.TexCoord = m_TexCoord[3];
	v3.TexIndex = m_TexIndex;

	return { v0, v1, v2, v3 };
}

Texture& Sprite::GetTexture()
{
	return *m_Texture;
}
