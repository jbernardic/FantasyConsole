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

class Shape {
public:
	Shape(float width, float height, glm::vec2 position);
	virtual void Draw() {};
	void SetTexture(const char* name);
	void RemoveTexture();
	void Scale(glm::vec2 times);
	void Rotate(float angle);
	void SetPosition(float posx, float posy);
	glm::vec2 GetPosition() { return m_Position; }
	void Translate(glm::vec2 vec);
	void SetColor(float a, float b, float c, float d);
	static unsigned int instance;
protected:
	glm::vec2 m_Position = glm::vec2(0.0f);
	glm::vec2 m_Size = glm::vec2(1.0);
	glm::mat4 m_Model = glm::mat4(1.0f);
	Shader* m_Shader = nullptr;
	Texture* m_Texture = nullptr;
	float m_Rotation = 0;
};
