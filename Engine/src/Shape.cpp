#include "Shape.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Renderer.h"

unsigned int Shape::instance = 0;

Shape::Shape(float* vert, unsigned int* indic, float width, float height, glm::vec2 pos, const VertexArray& va, unsigned int count)
	: vertices(vert), indices(indic), position(pos), va(va), elementCount(count)
{
	rm::LoadShader("Resources/Shape.shader", "shape" + std::to_string(instance));
	shader = &rm::GetShader("shape" + std::to_string(instance));
	model = glm::scale(model, glm::vec3(width, height, 1.0f));
	size = glm::vec2(width, height);
	collisionBounds.size = size;
	model = glm::translate(model, glm::vec3(position.x / size.x, position.y / size.y, 0.0f));

	shader->SetMatrix4("model", model);
	shader->SetInt("tex", 0);
	shader->SetFloat4("_color", 1.0f, 1.0f, 1.0f, 1.0f);
	instance++;

}
void Shape::SetTexture(const char* name) {
	Texture& _texture = ResourceManager::GetTexture(name);
	texture = &_texture;
	shader->SetInt("tex", 1);
	shader->SetInt("_texture", 0);
	hastexture = true;
}

void Shape::Scale(glm::vec2 times) {
	model = glm::scale(model, glm::vec3(times, 1.0f));
	size = size * times;
	collisionBounds.size = collisionBounds.size * times;
	shader->SetMatrix4("model", model);
}

void Shape::Rotate(float angle) {
	rotation = rotation + angle;
	model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
	shader->SetMatrix4("model", model);
}

void Shape::SetPosition(float posx, float posy) {
	glm::vec2 pos = glm::vec2(posx, posy);
	float rot = rotation;
	Rotate(-rot);
	model = glm::translate(model, glm::vec3(-position.x / size.x, -position.y / size.y, 0.0f));
	position = pos;
	model = glm::translate(model, glm::vec3(pos.x / size.x, pos.y / size.y, 0.0f));
	Rotate(rot);
	shader->SetMatrix4("model", model);
}

void Shape::Translate(glm::vec2 vec) {
	position = position + vec;
	model = glm::translate(model, glm::vec3(vec.x / size.x, vec.y / size.y, 0.0f));
	shader->SetMatrix4("model", model);
}

void Shape::ScaleCollisionBounds(glm::vec2 times) {
	collisionBounds.size = size * times;
}

void Shape::SetCollisisionBoundsType(BoundsType type) {
	collisionBounds.type = type;
}

void Shape::FillColor(float a, float b, float c, float d){
	shader->SetInt("tex", 0);
	shader->SetFloat4("_color", a, b, c, d);
	hastexture = false;
}