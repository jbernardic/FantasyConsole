#include"Renderer.h"
#include <algorithm>
#include <glad/glad.h>

void Renderer::Draw(const Shape& shape) {
	shape.GetShader().Bind();
	shape.GetVertexArray().Bind();
	if (shape.HasTexture()) { shape.GetTexture().Bind(); }

	if (shape.IsPolygon()) {
		lcall(glDrawArrays(GL_TRIANGLE_FAN, 0, shape.GetElementCount()));
	}
	else {
		lcall(glDrawElements(GL_TRIANGLES, shape.GetElementCount(), GL_UNSIGNED_INT, nullptr));
	}

	if (shape.HasTexture()) shape.GetTexture().UnBind();


}
void Renderer::Clear() {
	glClearColor(0.5, 0.5, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}