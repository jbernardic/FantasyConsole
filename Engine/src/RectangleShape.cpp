#include "RectangleShape.h"

RectangleShape::RectangleShape(float x, float y, float width, float height) : Shape(glm::vec2(x, y), width, height)
{
	m_VA.AddBuffer(m_VB, 0, 2, GL_FLOAT, 4);
	m_VA.AddBuffer(m_VB, 1, 2, GL_FLOAT, 4);
	m_IB.Bind();
}

void RectangleShape::Draw() {
	m_Shader->Bind();
	m_VA.Bind();
	m_IB.Bind();
	if (m_Texture) { m_Texture->Bind(); }
	lcall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
	if (m_Texture) m_Texture->UnBind();
}