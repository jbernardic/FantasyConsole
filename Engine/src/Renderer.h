#pragma once
#include "ErrorHandler.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RectangleShape.h"
#include "PolygonShape.h"

class Renderer {
public:
	static void Draw(const Shape& shape);
	static void Clear();
private:
	Renderer();

};
