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
	bool IsPolygon() const { return isPolygon; }
	void SetPolygon(bool a) { isPolygon = a; }
	glm::vec2 GetPosition() const { return position; };
	glm::vec2 GetSize() const { return size; }
	unsigned int* GetIndices() const { return indices; }
	float* GetVertices() const { return vertices; }
	const Shader& GetShader() const { return *shader; }
	const Texture& GetTexture() const { return *texture; };
	const VertexArray& GetVertexArray() const { return va; }
	Bounds GetCollisionBounds() const { return collisionBounds; }
	unsigned int GetID() const { return va.GetRendID(); }
	bool HasTexture() const { return hastexture; }
	unsigned int GetElementCount() const { return elementCount; }
	static unsigned int instance;
private:
	float* vertices;
	unsigned int* indices;
	const VertexArray& va;
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 size = glm::vec2(1.0);
	glm::mat4 model = glm::mat4(1.0f);
	Shader* shader = nullptr;
	Texture* texture = nullptr;
	float rotation = 0;
	bool hastexture = false;
	bool isPolygon = false;
	Bounds collisionBounds = { glm::vec2(1.0), position, BoundsType::RECTANGLE };
	unsigned int elementCount;
};
