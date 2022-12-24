#include "RectangleShape.h"

RectangleShape::RectangleShape(float width, float height, float x, float y) : Shape(vertices, indices, width, height, glm::vec2(x, y), va, 6)
{
	va.AddBuffer(vb, 0, 2, GL_FLOAT, 4);
	va.AddBuffer(vb, 1, 2, GL_FLOAT, 4);
	ib.Bind();
}