#include "Shape.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Renderer.h"

unsigned int Shape::instance = 0;

Shape::Shape(float* vert, unsigned int* indic, float width, float height, glm::vec2 pos, const VertexArray& va, unsigned int count)
	: m_Position(pos), m_VA(va), m_ElementCount(count)
{
	rm::LoadShader("Resources/Shape.Shader", "shape" + std::to_string(instance));
	m_Shader = &rm::GetShader("shape" + std::to_string(instance));
	m_Model = glm::scale(m_Model, glm::vec3(width, height, 1.0f));
	m_Size = glm::vec2(width, height);
	m_CollisionBounds.size = m_Size;
	m_Model = glm::translate(m_Model, glm::vec3(m_Position.x / m_Size.x, m_Position.y / m_Size.y, 0.0f));

	m_Shader->SetMatrix4("model", m_Model);
	m_Shader->SetInt("tex", 0);
	m_Shader->SetFloat4("_color", 1.0f, 1.0f, 1.0f, 1.0f);
	instance++;

}
void Shape::SetTexture(const char* name) {
	Texture& texture = ResourceManager::GetTexture(name);
	m_Texture = &texture;
	m_Shader->SetInt("tex", 1);
	m_Shader->SetInt("_texture", 0);
	m_HasTexture = true;
}

void Shape::Scale(glm::vec2 times) {
	m_Model = glm::scale(m_Model, glm::vec3(times, 1.0f));
	m_Size = m_Size * times;
	m_CollisionBounds.size = m_CollisionBounds.size * times;
	m_Shader->SetMatrix4("m_Model", m_Model);
}

void Shape::Rotate(float angle) {
	m_Rotation = m_Rotation + angle;
	m_Model = glm::translate(m_Model, glm::vec3(0.5f, 0.5f, 0.0f));
	m_Model = glm::rotate(m_Model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	m_Model = glm::translate(m_Model, glm::vec3(-0.5f, -0.5f, 0.0f));
	m_Shader->SetMatrix4("m_Model", m_Model);
}

void Shape::SetPosition(float posx, float posy) {
	glm::vec2 pos = glm::vec2(posx, posy);
	float rot = m_Rotation;
	Rotate(-rot);
	m_Model = glm::translate(m_Model, glm::vec3(-m_Position.x / m_Size.x, -m_Position.y / m_Size.y, 0.0f));
	m_Position = pos;
	m_Model = glm::translate(m_Model, glm::vec3(pos.x / m_Size.x, pos.y / m_Size.y, 0.0f));
	Rotate(rot);
	m_Shader->SetMatrix4("m_Model", m_Model);
}

void Shape::Translate(glm::vec2 vec) {
	m_Position = m_Position + vec;
	m_Model = glm::translate(m_Model, glm::vec3(vec.x / m_Size.x, vec.y / m_Size.y, 0.0f));
	m_Shader->SetMatrix4("m_Model", m_Model);
}

void Shape::ScaleCollisionBounds(glm::vec2 times) {
	m_CollisionBounds.size = m_Size * times;
}

void Shape::SetCollisisionBoundsType(BoundsType type) {
	m_CollisionBounds.type = type;
}

void Shape::FillColor(float a, float b, float c, float d){
	m_Shader->SetInt("tex", 0);
	m_Shader->SetFloat4("_color", a, b, c, d);
	m_HasTexture = false;
}