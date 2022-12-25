#include "RectangleShape.h"

RectangleShape::RectangleShape(float width, float height, float x, float y) : Shape(m_Vertices, m_Indices, width, height, glm::vec2(x, y), m_VA, 6)
{
	m_VA.AddBuffer(m_VB, 0, 2, GL_FLOAT, 4);
	m_VA.AddBuffer(m_VB, 1, 2, GL_FLOAT, 4);
	m_IB.Bind();
}