#include<GLM/glm.hpp>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Variables.h"
#include "Shape.h"

#pragma once

class RectangleShape : public Shape{
public:
	RectangleShape(float width = 100.0f, float height = 100.0f, float x = 0.0f, float y = 0.0f);
private:
	float m_Vertices[16] = {
		// Pos      // Tex
		0.0f, 1.0f,  0.0f,-1.0f,
		1.0f, 1.0f,  1.0f,-1.0f,
		1.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 0.0f,
	};

	unsigned int m_Indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	VertexArray m_VA;
	VertexBuffer m_VB = { m_Vertices, 4 * 4 * sizeof(float) };
	IndexBuffer m_IB = IndexBuffer(m_Indices, 6);
};

