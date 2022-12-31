#include "ShapeRenderer.h"
#include "RectangleShape.h"
#include <glad/glad.h>
#include <gl/GL.h>

void ShapeRenderer::Clear()
{
	m_ShapeIndex = 0;
	m_Shapes.clear();
}

void ShapeRenderer::Draw()
{
	for (int i = 0; i < m_Shapes.size(); i++) {
		if (i < m_ShapeIndex) {
			m_Shapes[i]->Draw();
		}
		else m_Shapes.pop_back();
	}
	m_ShapeIndex = 0;
}

void ShapeRenderer::DrawRectangle(glm::vec4 rect, glm::vec4 color)
{
	if (m_ShapeIndex < m_Shapes.size()) {
		m_Shapes[m_ShapeIndex]->SetPosition(rect.x, rect.y);
		glm::vec2 size = m_Shapes[m_ShapeIndex]->GetSize();
		m_Shapes[m_ShapeIndex]->Scale(glm::vec2(rect.z / size.x, rect.w / size.y));
		m_Shapes[m_ShapeIndex]->SetColor(color.x, color.y, color.z, color.w);
	}
	else {
		m_Shapes.push_back(std::make_unique<RectangleShape>(rect.x, rect.y, rect.z, rect.w));
		m_Shapes[m_ShapeIndex]->SetColor(color.x, color.y, color.z, color.w);
	}
	m_ShapeIndex++;
	
}
void ShapeRenderer::DrawCircle(glm::vec2 position, glm::vec4 color)
{
}
