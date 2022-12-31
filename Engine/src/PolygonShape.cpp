#include "PolygonShape.h"

PolygonShape::PolygonShape(float x, float y, float r, unsigned int pNum)
	:m_PointNumber(pNum), m_Radius(r), Shape(glm::vec2(x, y), r, r)
{
	std::vector<float> vert;
	std::vector<float> coords;
	vert.push_back(0.0f);
	vert.push_back(0.0f);
	float pi = 3.14159265359f;
	for (float theta = 0.0f; theta < 2 * pi; theta+=2*pi/pNum) {
		float x = glm::cos(theta)+0.5f;
		float y = glm::sin(theta)+0.5f;
		vert.push_back(x);
		vert.push_back(y);

	}
	vert.push_back(glm::cos(0.0f) + 0.5f);
	vert.push_back(glm::sin(0.0f) + 0.5f);

	//TexCoords
	for (unsigned int i = 0; i < vert.size(); i+=2) {
		float x = (vert[i]+0.5f)*0.5f;
		float y = (vert[i+1]+0.5f)*-0.5f;
		coords.push_back(x);
		coords.push_back(y);
	}
	unsigned int n = 0;
	size_t s = coords.size() + vert.size();
	for (unsigned int i = 2; i < s; i+=4) {
		vert.insert(vert.begin() + i, coords[n + 1]);
		vert.insert(vert.begin() + i, coords[n]);
		n += 2;
	}

	m_VB = std::make_shared<VertexBuffer>(vert.data(), vert.size() * sizeof(float));
	m_VA.AddBuffer(*m_VB, 0, 2, GL_FLOAT, 4);
	m_VA.AddBuffer(*m_VB, 1, 2, GL_FLOAT, 4);
}

void PolygonShape::Draw() {
	m_Shader->Bind();
	m_VA.Bind();
	if (m_Texture) { m_Texture->Bind(); }
	lcall(glDrawArrays(GL_TRIANGLE_FAN, 0, m_PointNumber * 4 + 8));
	if (m_Texture) { m_Texture->UnBind(); }
}