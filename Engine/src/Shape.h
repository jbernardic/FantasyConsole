#pragma once
#include<iostream>
#include <vector>
#include<GLM/glm.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"

typedef ResourceManager rm;

enum class BoundsType {
	RECTANGLE = 0, CIRCLE = 1
};

struct Bounds {
	glm::vec2 size;
	const glm::vec2& pos;
	BoundsType type;
};

class Shape {
public:
	Shape(float* vertices, unsigned int* indices, float width, float height, glm::vec2 position, const VertexArray& va, unsigned int count);
	void SetTexture(const char* name);
	void Scale(glm::vec2 times);
	void Rotate(float angle);
	void SetPosition(float posx, float posy);
	void Translate(glm::vec2 vec);
	void ScaleCollisionBounds(glm::vec2 times);
	void SetCollisisionBoundsType(BoundsType type);
	void FillColor(float a, float b, float c, float d);
	bool IsPolygon() const { return m_IsPolygon; }
	void SetPolygon(bool a) { m_IsPolygon = a; }
	glm::vec2 GetPosition() const { return m_Position; };
	glm::vec2 GetSize() const { return m_Size; }
	const Shader& GetShader() const { return *m_Shader; }
	const Texture& GetTexture() const { return *m_Texture; };
	const VertexArray& GetVertexArray() const { return m_VA; }
	Bounds GetCollisionBounds() const { return m_CollisionBounds; }
	unsigned int GetID() const { return m_VA.GetRendID(); }
	bool HasTexture() const { return m_HasTexture; }
	unsigned int GetElementCount() const { return m_ElementCount; }
	static unsigned int instance;
private:
	const VertexArray& m_VA;
	glm::vec2 m_Position = glm::vec2(0.0f);
	glm::vec2 m_Size = glm::vec2(1.0);
	glm::mat4 m_Model = glm::mat4(1.0f);
	Shader* m_Shader = nullptr;
	Texture* m_Texture = nullptr;
	float m_Rotation = 0;
	bool m_HasTexture = false;
	bool m_IsPolygon = false;
	Bounds m_CollisionBounds = { glm::vec2(1.0), m_Position, BoundsType::RECTANGLE };
	unsigned int m_ElementCount;
};
