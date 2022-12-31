#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Shape.h"
class ShapeRenderer
{
public:
	void Clear();
	void Draw();
	void DrawRectangle(glm::vec4 rect, glm::vec4 color);
	void DrawCircle(glm::vec2 position, glm::vec4 color);
private:
	std::vector<std::unique_ptr<Shape>> m_Shapes;
	unsigned int m_ShapeIndex;
};

