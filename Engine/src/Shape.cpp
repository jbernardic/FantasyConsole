#include "Shape.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

unsigned int Shape::instance = 0;

Shape::Shape(glm::vec2 pos, float width, float height)
	: m_Position(pos)
{
	rm::LoadShader("Resources/Shape.Shader", "shape" + std::to_string(instance));
	m_Shader = &rm::GetShader("shape" + std::to_string(instance));
	m_Model = glm::scale(m_Model, glm::vec3(width, height, 1.0f));
	m_Size = glm::vec2(width, height);
	m_Model = glm::translate(m_Model, glm::vec3(m_Position.x / m_Size.x, m_Position.y / m_Size.y, 0.0f));

	m_Shader->SetMatrix4("model", m_Model);
	m_Shader->SetFloat4("color", 1.0f, 1.0f, 1.0f, 1.0f);
	instance++;

}

void Shape::RemoveTexture() {
	m_Texture = nullptr;
	m_Shader->SetInt("hasTexture", 0);
}

void Shape::SetTexture(const char* name) {
	Texture& texture = ResourceManager::GetTexture(name);
	m_Texture = &texture;
	m_Shader->SetInt("hasTexture", 1);
	m_Shader->SetInt("Texture", 0);
}

void Shape::Scale(glm::vec2 times) {
	m_Model = glm::scale(m_Model, glm::vec3(times, 1.0f));
	m_Size = m_Size * times;
	m_Shader->SetMatrix4("model", m_Model);
}

void Shape::Rotate(float angle) {
	m_Rotation = m_Rotation + angle;
	m_Model = glm::translate(m_Model, glm::vec3(0.5f, 0.5f, 0.0f));
	m_Model = glm::rotate(m_Model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	m_Model = glm::translate(m_Model, glm::vec3(-0.5f, -0.5f, 0.0f));
	m_Shader->SetMatrix4("model", m_Model);
}

void Shape::SetPosition(float posx, float posy) {
	glm::vec2 pos = glm::vec2(posx, posy);
	float rot = m_Rotation;
	Rotate(-rot);
	m_Model = glm::translate(m_Model, glm::vec3(-m_Position.x / m_Size.x, -m_Position.y / m_Size.y, 0.0f));
	m_Position = pos;
	m_Model = glm::translate(m_Model, glm::vec3(pos.x / m_Size.x, pos.y / m_Size.y, 0.0f));
	Rotate(rot);
	m_Shader->SetMatrix4("model", m_Model);
}

void Shape::Translate(glm::vec2 vec) {
	m_Position = m_Position + vec;
	m_Model = glm::translate(m_Model, glm::vec3(vec.x / m_Size.x, vec.y / m_Size.y, 0.0f));
	m_Shader->SetMatrix4("model", m_Model);
}

void Shape::SetColor(float a, float b, float c, float d){
	m_Shader->SetFloat4("color", a, b, c, d);
}